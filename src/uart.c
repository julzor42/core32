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
#include <core32/uart.h>

#ifdef UART_CONSOLE

void _mon_putc(char c)
{
  while (UxSTA(UART_CONSOLE) & USTA_TXBF);
  UxTXREG(UART_CONSOLE) = c;
}

int _mon_getc(int canblock)
{
  while (!(UxSTA(UART_CONSOLE) & USTA_URXDA));
  return UxRXREG(UART_CONSOLE);
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

void UART_PutChar(unsigned int Port, unsigned char Data)
{
  while (UxSTA(Port) & USTA_TXBF);
  UxTXREG(Port) = Data;
}

void UART_PutString(unsigned int Port, const unsigned char* Data)
{
  while (*Data)
    UART_PutChar(Port, *Data++);
}

void UART_Write(unsigned int Port, const unsigned char* Data, unsigned int Length)
{
  while (--Length)
    UART_PutChar(Port, *Data++);
}

unsigned char UART_GetChar(unsigned int Port)
{
  while (!(UxSTA(Port) & USTA_URXDA));
  return UxRXREG(Port);
}

void UART_Read(unsigned int Port, unsigned char* Data, unsigned int Length)
{
  while (--Length)
    (*Data++) = UART_GetChar(Port);
}