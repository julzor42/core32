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
#ifdef __PIC32MX__

#include <core32.h>
#include <core32/uart.h>

#ifdef UART_CONSOLE

void _mon_putc(char c)
{
  while (UART_IsFull(UART_CONSOLE));
  UxTXREG(UART_CONSOLE) = c;
}

int _mon_getc(int canblock)
{
  if (canblock)
  {
    while (!UART_HasData(UART_CONSOLE));
    return UxRXREG(UART_CONSOLE);
  }

  if (UART_HasData(UART_CONSOLE))
    return UxRXREG(UART_CONSOLE);

  return 0;
}

#endif

void UART_Initialize(unsigned int Port, unsigned int Baud, unsigned int RdWr)
{
  int Div4 = 0;
  
  // Disable and clear UART
  UxMODE(Port) = 0;
  
  PBDIV1_CYCLE_WAIT();
    
  if (Div4)               UxMODESET(Port) = UMODE_BRGH;
  if (RdWr & UART_WRITE)  UxSTASET(Port)  = USTA_UTXEN;
  if (RdWr & UART_READ)   UxSTASET(Port)  = USTA_URXEN;

  UxBRG(Port) = PBCLK / (Div4 ? 4 : 16) / Baud - 1;
    
  UART_Enable(Port);
}

void UART_PutChar(unsigned int Port, char Data)
{
  while (UART_IsFull(Port));
  UxTXREG(Port) = Data;
}

void UART_PutString(unsigned int Port, const char* Data)
{
  while (*Data)
    UART_PutChar(Port, *Data++);
}

void UART_Write(unsigned int Port, const char* Data, unsigned int Length)
{
  while (--Length)
    UART_PutChar(Port, *Data++);
}

char UART_GetChar(unsigned int Port)
{
  while (!UART_HasData(Port));
  return UxRXREG(Port);
}

void UART_Read(unsigned int Port, char* Data, unsigned int Length)
{
  while (--Length)
    (*Data++) = UART_GetChar(Port);
}

void UART_ReadLine(unsigned int Port, char* Data, unsigned int MaxLength)
{
  while (--MaxLength > 0)
  {
    *Data = UART_GetChar(Port);
    
    if (*Data == '\n')
      break;

    Data++;
  }

  *Data = 0;
}

void UART_SetInterrupt(unsigned int Port, unsigned int Mode, unsigned int Priority, unsigned int SubPriority)
{
  UART_EnableInterrupt(Port, DISABLED);
  UART_EnableTXInterrupt(Port, DISABLED);
  UART_EnableRXInterrupt(Port, DISABLED);
  
  switch (Port)
    {
    case UART_2:
      IPC8bits.U2IP = Priority;
      IPC8bits.U2IS = SubPriority;
      break;
    }

  UART_ClearInterrupt(Port);
  UART_ClearTXInterrupt(Port);
  UART_ClearRXInterrupt(Port);
  
  UART_EnableInterrupt(Port, (Mode != 0) ? 1 : 0);
  UART_EnableTXInterrupt(Port, (Mode & UART_WRITE) ? 1 : 0);
  UART_EnableRXInterrupt(Port, (Mode & UART_READ) ? 1 : 0);
}

void UART_EnableInterrupt(unsigned int Port, unsigned int Enabled)
{
  switch (Port)
    {
    case UART_2: IEC1bits.U2EIE = Enabled; break;
    }
}

void UART_EnableTXInterrupt(unsigned int Port, unsigned int Enabled)
{
  switch (Port)
    {
    case UART_2: IEC1bits.U2TXIE = Enabled; break;
    }
}

void UART_EnableRXInterrupt(unsigned int Port, unsigned int Enabled)
{
  switch (Port)
    {
    case UART_2: IEC1bits.U2RXIE = Enabled; break;
    }
}

void UART_ClearInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: IFS1bits.U2EIF = 0; break;
    }
}

void UART_ClearTXInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: IFS1bits.U2TXIF = 0; break;
    }
}

void UART_ClearRXInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: IFS1bits.U2RXIF = 0; break;
    }
}

unsigned int UART_CheckInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: return IFS1bits.U2EIF;
    }

  return 0;
}

unsigned int UART_CheckTXInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: return IFS1bits.U2TXIF;
    }

  return 0;
}

unsigned int UART_CheckRXInterrupt(unsigned int Port)
{
  switch (Port)
    {
    case UART_2: return IFS1bits.U2RXIF;
    }

  return 0;
}
#endif