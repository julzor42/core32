/*
  MIT License

  Copyright (c) 2016 Julien Delmotte

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include <core32.h>
#include <esp8266/esp8266.h>

typedef struct  WifiContext_s
{
  unsigned int  Ticks;
  unsigned int  NeedReset;
  
  unsigned int  ConnectionFlags;
  unsigned char IpAddress[16];
  
  unsigned int  TcpState;
  unsigned int  TcpFlags;
  unsigned char TcpHost[128];
  unsigned int  TcpPort;
  
  unsigned char OutputBuffer[1024];
  unsigned int  OBRCur;
  unsigned int  OBWCur;
  unsigned int  OBSize;
  unsigned int  OBSizeCopy;
  
  unsigned char InputBuffer[1024];
  unsigned int  IBRCur;
  unsigned int  IBWCur;
  unsigned int  IBSize;
  unsigned int  IBRecv;
  
  unsigned int ByteModeCount;
    
}               WifiContext_t;

#define ESP8266_CONNECTED         0x00000001
#define ESP8266_HASIP             0x00000020
#define ESP8266_IDLE              0x00000040

#define ESP8266_TCP_OFFLINE       0
#define ESP8266_TCP_CONNREQUEST   1
#define ESP8266_TCP_CONNECTING    2
#define ESP8266_TCP_CONNECTED     3

#define ESP8266_TCPF_CLOSING      0x00000001
#define ESP8266_TCPF_SENDING      0x00000002
#define ESP8266_TCPF_ERROR        0x00000004

static void             Task_ESP8266      (Task_t* pTask);
static WifiContext_t    g_Wifi;

// UART input buffer
volatile unsigned char  UIBuffer[1024];
volatile unsigned int   UIBWCursor;
volatile unsigned int   UIBRCursor;
volatile unsigned int   UIBCount;
volatile unsigned int   UIBLines;

// UART output buffer
volatile unsigned char  UOBuffer[1024];
volatile unsigned int   UOBWCursor;
volatile unsigned int   UOBRCursor;
volatile unsigned int   UOBCount;

static inline unsigned char PeekTcpOutputBuffer()                 { PEEK_FUNC(g_Wifi.OutputBuffer, g_Wifi.OBRCur);     }
static inline void          PokeTcpOutputBuffer(unsigned char c)  { POKE_FUNC(g_Wifi.OutputBuffer, g_Wifi.OBWCur, c);  }
static inline unsigned char PeekTcpInputBuffer()                  { PEEK_FUNC(g_Wifi.InputBuffer, g_Wifi.IBRCur);      }
static inline void          PokeTcpInputBuffer(unsigned char c)   { POKE_FUNC(g_Wifi.InputBuffer, g_Wifi.IBWCur, c);   }

static inline unsigned char PeekOBuffer()                         { PEEK_FUNC(UOBuffer, UOBRCursor);                   }
static inline void          PokeOBuffer(unsigned char c)          { POKE_FUNC(UOBuffer, UOBWCursor, c);                }
static inline unsigned char PeekIBuffer()                         { PEEK_FUNC(UIBuffer, UIBRCursor);                   }
static inline void          PokeIBuffer(unsigned char c)          { POKE_FUNC(UIBuffer, UIBWCursor, c);                }

//
// UART interrupt
//
void __ISR(_UART_5_VECTOR, ipl2auto) U5Int()
{
  if (IEC2bits.U5RXIE && IFS2bits.U5RXIF)
  {
    while (U5STAbits.URXDA)
    {
      unsigned char c = U5RXREG;
      PokeIBuffer(c);
      UIBCount++;

      // New line
      if (c == 10)
        UIBLines++;
    }
    IFS2bits.U5RXIF = 0;
  }
  
  if (IEC2bits.U5TXIE && IFS2bits.U5TXIF)
  {
    while (!U5STAbits.UTXBF && UOBCount)
    {
      U5TXREG = PeekOBuffer();
      UOBCount--;
    }
    
    if (UOBCount == 0)
      IEC2bits.U5TXIE = 0;
    
    IFS2bits.U5TXIF = 0;
  }
}

//
// Buffer management functions
//


static int Wifi_ReadLine(char* data)
{
  IEC2bits.U5RXIE = 0;
  
  if (g_Wifi.ByteModeCount)
  {
    while (UIBCount && g_Wifi.ByteModeCount)
    {
      *data++ = PeekIBuffer();
      UIBCount--;
      g_Wifi.ByteModeCount--;
    }
    *data = 0;
    IEC2bits.U5RXIE = 1;
    return 1;
  }
  
  if (UIBLines)
  {
    unsigned char c = 0;
    while (c != 10)
    {
      c = PeekIBuffer();
      UIBCount--;
      *data++ = c;
    }

    // Remove \r\n
    *(data - 2) = 0;
    
    UIBLines--;    
    IEC2bits.U5RXIE = 1;
    return 1;
  }
  
  IEC2bits.U5RXIE = 1;
  return 0;
}

static void Wifi_Clear()
{
  IEC2bits.U5TXIE = 0;
  IEC2bits.U5RXIE = 0;
  UIBRCursor      = 0;
  UIBWCursor      = 0;
  UIBLines        = 0;
  UIBCount        = 0;
  UOBCount        = 0;
  UOBRCursor      = 0;
  UOBWCursor      = 0;
  IEC2bits.U5RXIE = 1;
  
  g_Wifi.Ticks    = 0;
}

static void Wifi_BeginPush()
{
  IEC2bits.U5TXIE = 0;
#ifdef ESP8266_DEBUG
  printf("-> ");
#endif
}

static void Wifi_Push(const char* Data)
{
#ifdef ESP8266_DEBUG
  printf("%s", Data);
#endif  
  while (*Data)
  {
    PokeOBuffer(*Data++);
    UOBCount++;
  }
}

static void Wifi_EndPush()
{
#ifdef ESP8266_DEBUG
  printf("\n");
#endif
  IEC2bits.U5TXIE = 1;
}

static void Wifi_PushSingle(const char* Data)
{
#ifdef ESP8266_DEBUG
  printf("%s", Data);
#endif
  IEC2bits.U5TXIE = 0;
  while (*Data)
  {
    PokeOBuffer(*Data++);
    UOBCount++;
  }
  IEC2bits.U5TXIE = 1;
}

//
// ESP8266 state machine
//
enum WifiStates
{
  STATE_WIFI_WAITREADY = 100,
  STATE_WIFI_WAITCONNECTED,
  STATE_WIFI_WAITGOTIP,
  STATE_WIFI_WAITIP,
  
  STATE_WIFI_TCPWAITCONNECT,
  STATE_WIFI_TCPWAITDISCONNECT,
  STATE_WIFI_TCPPRESEND,
  STATE_WIFI_TCPSENT,
  STATE_WIFI_TCPRECV,
};

static int SubTask_0(Task_t* pTask, unsigned char* sLine)
{
  if (g_Wifi.NeedReset)
  {
    g_Wifi.NeedReset = 0;
    pTask->State = TASK_START;
  }
  
  switch (pTask->State)
  {
    case TASK_START:
      // Start module
      Wifi_Clear();
      Wifi_PushSingle("AT+RST\r\n");        
      pTask->State = STATE_WIFI_WAITREADY;
      return 1;
      
    case TASK_IDLE:
      if (g_Wifi.TcpState == ESP8266_TCP_CONNREQUEST)
      {
        // TCP connection request
        g_Wifi.TcpState = ESP8266_TCP_CONNECTING;
        char sTmp[6] = {0};
        utoa(sTmp, g_Wifi.TcpPort, 10);
  
        Wifi_BeginPush();
        Wifi_Push("AT+CIPSTART=\"TCP\",\"");
        Wifi_Push(g_Wifi.TcpHost);
        Wifi_Push("\",");
        Wifi_Push(sTmp);
        Wifi_Push("\r\n");
        Wifi_EndPush();
  
        pTask->State = STATE_WIFI_TCPWAITCONNECT;
        return 1;
      }
      
      if (g_Wifi.OBSize)
      {
        // There are bytes to send
        char sTmp[6] = {0};

        // Keep a copy of the number of bytes to send
        g_Wifi.OBSizeCopy = g_Wifi.OBSize;
        g_Wifi.OBSize     = 0;        
        
        utoa(sTmp, g_Wifi.OBSizeCopy, 10);

        Wifi_BeginPush();
        Wifi_Push("AT+CIPSEND=");
        Wifi_Push(sTmp);
        Wifi_Push("\r\n");
        Wifi_EndPush();
        
        pTask->State = STATE_WIFI_TCPPRESEND;
        return 1;
      }
      
      if (g_Wifi.TcpFlags & ESP8266_TCPF_CLOSING)
      {
        Wifi_PushSingle("AT+CIPCLOSE\r\n");
        pTask->State = STATE_WIFI_TCPWAITDISCONNECT;
        return 1;
      }
      
      if (sLine && strcmp(sLine, "CLOSED") == 0)
      {
        g_Wifi.TcpFlags = 0;
        g_Wifi.TcpState = ESP8266_TCP_OFFLINE;
        return 1;
      }
           
      if (sLine && strncmp(sLine, "+IPD,", 5) == 0)
      {
        unsigned char* p  = sLine + 5;
        unsigned char* pN = p;
        while (*p)
        {
          if (*p == ':')
          {
            *p++ = 0;
            break;
          }
          p++;
        }
        
        g_Wifi.IBSize = atoi(pN) - 2; // TODO: -2 because +IPD contains first line, with removed \r\n
        g_Wifi.IBRecv = 0;
        
        while (*p && g_Wifi.IBSize)
        {
          PokeTcpInputBuffer(*p++);
          g_Wifi.IBSize--;
          g_Wifi.IBRecv++;
        }
        
        if (g_Wifi.IBSize > 0)
        {
          g_Wifi.ByteModeCount = g_Wifi.IBSize;
          pTask->State = STATE_WIFI_TCPRECV;
        }
        return 1;
      }
           
      return 1;
  }
  
  return 0;
}

static int SubTask_Connection(Task_t* pTask, unsigned char* sLine)
{
  switch (pTask->State)
  {
    case STATE_WIFI_WAITREADY:
      if (sLine && strcmp(sLine, "ready") == 0)       pTask->State = STATE_WIFI_WAITCONNECTED;
      else if (sLine && strcmp(sLine, "ERROR") == 0)  Task_SetDelay(pTask, 1000000, TASK_START);
      else if (!sLine && g_Wifi.Ticks > 100000)       g_Wifi.NeedReset = 1;
      
      return 1;
      
    case STATE_WIFI_WAITCONNECTED:
      if (sLine && strcmp(sLine, "WIFI CONNECTED") == 0)
      {
        g_Wifi.ConnectionFlags |= ESP8266_CONNECTED;
        pTask->State = STATE_WIFI_WAITGOTIP;
      }
      return 1;
      
    case STATE_WIFI_WAITGOTIP:
      if (sLine && strcmp(sLine, "WIFI GOT IP") == 0)
      {
        // Module has IP, ask for it
        Wifi_PushSingle("AT+CIFSR\r\n");
        pTask->State = STATE_WIFI_WAITIP;
      }
      return 1;
      
    case STATE_WIFI_WAITIP:
      if (sLine && strcmp(sLine, "OK") == 0)
      {
        // Operation completed
        g_Wifi.ConnectionFlags |= ESP8266_HASIP;
        pTask->State = TASK_IDLE;
      }
      else if (sLine && strcmp(sLine, "ERROR") == 0) Task_SetDelay(pTask, 1000000, TASK_START); // Reset!
      else if (sLine && strncmp(sLine, "+CIFSR:STAIP", 12) == 0)
      {
        // Received the IP address
        
        // Remove ending " from line
        unsigned char* p = sLine;
        for (p = sLine; *p; ++p)
          if (*p == '"')
            *p = 0;
        
        // Store IP
        strcpy(g_Wifi.IpAddress, sLine + 14);
      }
      
      return 1;
  }

  return 0;
}

static int SubTask_Tcp(Task_t* pTask, unsigned char* sLine)
{
  switch (pTask->State)
  {
    case STATE_WIFI_TCPWAITCONNECT:
      if (sLine && strcmp(sLine, "OK") == 0)
      {
        // Connection established
        g_Wifi.TcpState = ESP8266_TCP_CONNECTED;
        pTask->State    = TASK_IDLE;
      }
      else if (sLine && strcmp(sLine, "ERROR") == 0)
      {
        // Failed to connect
        g_Wifi.TcpFlags |= ESP8266_TCPF_ERROR;
        g_Wifi.TcpState  = ESP8266_TCP_OFFLINE;
        pTask->State     = TASK_IDLE;
      }
      return 1;
      
    case STATE_WIFI_TCPWAITDISCONNECT:
      if (sLine && (strcmp(sLine, "OK") == 0 || strcmp(sLine, "ERROR") == 0))
      {
        // Disconnected)
        g_Wifi.TcpFlags &= ~ESP8266_TCPF_CLOSING;
        g_Wifi.TcpState  = ESP8266_TCP_OFFLINE;
        pTask->State     = TASK_IDLE;
      }
      return 1;
      
    case STATE_WIFI_TCPPRESEND:
      if (sLine && strcmp(sLine, "OK") == 0)
      {
        // Module is waiting for OBSizeCopy bytes
        unsigned int  n           = 0;
        unsigned char sSend[1024] = {0};
        // Copy send buffer
        while (g_Wifi.OBSizeCopy)
        {
          sSend[n++] = PeekTcpOutputBuffer(); 
          g_Wifi.OBSizeCopy--;
        }
        Wifi_PushSingle(sSend);
        pTask->State = STATE_WIFI_TCPSENT;
      }
      return 1;
      
      case STATE_WIFI_TCPSENT:
      if (sLine && strcmp(sLine, "SEND OK") == 0)
      {
        // Bytes sent
        pTask->State = TASK_IDLE;
      }
      return 1;
      
      case STATE_WIFI_TCPRECV:
      {
        if (sLine)
        {
          while (*sLine)
          {
            PokeTcpInputBuffer(*sLine++);
            g_Wifi.IBSize--; 
            g_Wifi.IBRecv++;
            
            if (g_Wifi.IBSize == 0)
            {
              pTask->State = TASK_IDLE;
              return 1;
            }
          }
        }
      }
      return 1;
  }
  
  return 0;
}

#define SUBTASK(name)   if (name(pTask, pLine)) return

void Task_ESP8266(Task_t* pTask)
{
  static unsigned char sLine[128];
  unsigned char*       pLine = 0;
  
  g_Wifi.Ticks++;
  
  if (Wifi_ReadLine(sLine))
    pLine = sLine;
  
#ifdef ESP8266_DEBUG
  if (pLine)
    printf("<- %s\n", pLine);
#endif
  
  SUBTASK(SubTask_0);
  SUBTASK(SubTask_Connection);
  SUBTASK(SubTask_Tcp);
}

//
// User functions
//
void ESP8266_Initialize()
{     
  memset(&g_Wifi, 0, sizeof(g_Wifi));
  Wifi_Clear();
    
  Task_Create(Task_ESP8266, 0);
  
  UART_Initialize(UART_5, 115200, UART_READWRITE);
  
  IPC12bits.U5IP  = 2;
  IFS2bits.U5RXIF = 0;
  IFS2bits.U5TXIF = 0;
  IEC2bits.U5RXIE = 1;    
}

int   ESP8266_IsOnline() { return g_Wifi.ConnectionFlags & ESP8266_HASIP; }
char* ESP8266_GetIP()    { return g_Wifi.IpAddress; }

int   ESP8266_TcpConnect(const char* Host, unsigned short Port)
{
  if (g_Wifi.TcpState != ESP8266_TCP_OFFLINE) return 0;
  
  strcpy(g_Wifi.TcpHost, Host);
  
  g_Wifi.TcpPort  = Port;
  g_Wifi.TcpFlags = 0;
  g_Wifi.TcpState = ESP8266_TCP_CONNREQUEST;
  
  return 1;
}

void ESP8266_TcpClose()       { g_Wifi.TcpFlags |= ESP8266_TCPF_CLOSING; }
int  ESP8266_TcpIsConnected() { return g_Wifi.TcpState == ESP8266_TCP_CONNECTED; }
int  ESP8266_TcpIsSending()   { return g_Wifi.TcpFlags & ESP8266_TCPF_SENDING; }
int  ESP8266_TcpIsErrorSet()  { return g_Wifi.TcpFlags & ESP8266_TCPF_ERROR; }

int ESP8266_TcpSend(const char* Data)
{
  if (g_Wifi.TcpState != ESP8266_TCP_CONNECTED)
    return 0;
  
  while (*Data)
  {
    PokeTcpOutputBuffer(*Data++);
    g_Wifi.OBSize++;
  }
  
  return 0;
}

int ESP8266_TcpRecv(char* Data)
{
  unsigned int nRecv = 0;
  
  if (g_Wifi.TcpState != ESP8266_TCP_CONNECTED)
    return -1;
  
  nRecv = g_Wifi.IBRecv;
  
  while (g_Wifi.IBRecv)
  {
    *Data++ = PeekTcpInputBuffer();
    g_Wifi.IBRecv--;
  }
  
  return nRecv;
}

void ESP8266_Reset()
{
  g_Wifi.NeedReset = 1;
}