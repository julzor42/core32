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
#ifndef _UART_H_
#define _UART_H_

#define BASEADDRESS_UART    0xBF806000
#define UxMODE_BASE(x)      _SFR_ADDR(BASEADDRESS_UART, 0x200, x)

//
// SFRs
//
#define UxTXREG(x)          _SFR(UxMODE_BASE(x) + 0x20)
#define UxRXREG(x)          _SFR(UxMODE_BASE(x) + 0x30)
#define UxBRG(x)            _SFR(UxMODE_BASE(x) + 0x40)
#define UxMODE(x)           _SFR(UxMODE_BASE(x))
#define UxMODECLR(x)        _SFR_CLR(UxMODE_BASE(x))
#define UxMODESET(x)        _SFR_SET(UxMODE_BASE(x))
#define UxSTA(x)            _SFR(UxMODE_BASE(x) + 0x10)
#define UxSTACLR(x)         _SFR_CLR(UxMODE_BASE(x) + 0x10)
#define UxSTASET(x)         _SFR_SET(UxMODE_BASE(x) + 0x10)
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
#define UART_IsEnabled(port)(UxMODE(Port) & UMODE_UARTEN)

//
// Functions
//
void          UART_Initialize     (unsigned int Port, unsigned int Baud, unsigned int RdWr);
void          UART_PutChar        (unsigned int Port, unsigned char Data);
void          UART_PutString      (unsigned int Port, const unsigned char* Data);
unsigned char UART_GetChar        (unsigned int Port);
void          UART_Write          (unsigned int Port, const unsigned char* Data, unsigned int Length);
void          UART_Read           (unsigned int Port, unsigned char* Data, unsigned int Length);

#ifndef UART_CONSOLE_SPEED
#define UART_CONSOLE_SPEED 115200
#endif

#endif /* _UART_H_ */
