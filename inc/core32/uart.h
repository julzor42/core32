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
#pragma once

//
// SFRs
//
#define UxMODE(x)           _SFR_KEY_PTR(UART, x, 0x00)
#define UxMODECLR(x)        _SFR_KET_CLR(UART, x, 0x00)
#define UxMODESET(x)        _SFR_KEY_SET(UART, x, 0x00)
#define UxSTA(x)            _SFR_KEY_PTR(UART, x, 0x10)
#define UxSTACLR(x)         _SFR_KET_CLR(UART, x, 0x10)
#define UxSTASET(x)         _SFR_KEY_SET(UART, x, 0x10)
#define UxTXREG(x)          _SFR_KEY_PTR(UART, x, 0x20)
#define UxRXREG(x)          _SFR_KEY_PTR(UART, x, 0x30)
#define UxBRG(x)            _SFR_KEY_PTR(UART, x, 0x40)
//
// Core32 Flags
//
#define UART_READ           0x01
#define UART_WRITE          0x02
#define UART_READWRITE      0x03

//
// UART ports
//
#ifdef PIC32MX4
#define UART_1              0
#define UART_2              1
#else
#define UART_1              0
#define UART_4              1
#define UART_3              2
#define UART_6              3
#define UART_2              4
#define UART_5              5
#endif

//
// Macros
//
#define UART_Enable(port)   UxMODESET(port) = UMODE_UARTEN
#define UART_Disable(port)  UxMODECLR(port) = UMODE_UARTEN
#define UART_IsEnabled(port)(UxMODE(port) & UMODE_UARTEN)
#define UART_HasData(port)  (UxSTA(port) & USTA_URXDA)
#define UART_IsFull(port)   (UxSTA(port) & USTA_TXBF)

//
// Functions
//
void          UART_Initialize       (unsigned int Port, unsigned int Baud, unsigned int RdWr);
void          UART_PutChar          (unsigned int Port, char Data);
void          UART_PutString        (unsigned int Port, const char* Data);
char          UART_GetChar          (unsigned int Port);
void          UART_Write            (unsigned int Port, const char* Data, unsigned int Length);
void          UART_Read             (unsigned int Port, char* Data, unsigned int Length);
void          UART_ReadLine         (unsigned int Port, char* Data, unsigned int MaxLength);

void	        UART_SetInterrupt	    (unsigned int Port, unsigned int Mode, unsigned int Priority, unsigned int SubPriority);

void	        UART_EnableInterrupt  (unsigned int Port, unsigned int Enabled);
void	        UART_EnableTXInterrupt(unsigned int Port, unsigned int Enabled);
void	        UART_EnableRXInterrupt(unsigned int Port, unsigned int Enabled);

void	        UART_ClearInterrupt   (unsigned int Port);
void	        UART_ClearTXInterrupt (unsigned int Port);
void	        UART_ClearRXInterrupt (unsigned int Port);

unsigned int  UART_CheckInterrupt   (unsigned int Port);
unsigned int  UART_CheckTXInterrupt (unsigned int Port);
unsigned int  UART_CheckRXInterrupt (unsigned int Port);

#ifndef UART_CONSOLE_SPEED
#define UART_CONSOLE_SPEED 115200
#endif

#ifdef UART_CONSOLE
#define Console_Write(s)          UART_PutString(UART_CONSOLE, (s))
#define Console_WriteChar(c)      UART_PutChar(UART_CONSOLE, (c))
#define Console_GetChar()         UART_GetChar(UART_CONSOLE)
#define Console_ReadLine(p, len)  UART_ReadLine(UART_CONSOLE, (p), (len))
#define Console_Read(p, len)      UART_Read(UART_CONSOLE, (p), (len))
#define Console_WriteLine(s)      do { Console_Write(s); Console_Write("\r\n"); } while (0)
#endif
