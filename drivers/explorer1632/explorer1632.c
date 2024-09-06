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
#include "explorer1632.h"
#include "core32conf.h"

void Board_Startup()
{
  System_Initialize();
  
#ifdef EX1632_USE_CONSOLE_RW
  UART_Initialize(UART_CONSOLE, 115200, UART_READ | UART_WRITE);
#elif  EX1632_USE_CONSOLE_WO
  UART_Initialize(UART_CONSOLE, 115200, UART_WRITE);
#elif  EX1632_USE_CONSOLE_RO
  UART_Initialize(UART_CONSOLE, 115200, UART_READ);
#endif

#ifdef EX1632_USE_SPI
  CS1_DISABLE();
  CS2_DISABLE();
  
  CS1_TRIS = 0;
  CS2_TRIS = 0;
#endif
  
#ifdef DRIVER_nt7603
  LCD_Init();
#endif
}

void EX1632_InitLeds()
{
#ifdef __PIC32MX__
  ADC_SetDigital(PINS_ALL);
#endif
  GPIO_SetOutput(PortA, PINS_ALL);
  GPIO_ClearBits(PortA, PINS_ALL);
}

void EX1632_InitButtons()
{
  GPIO_InitButton(S3);
  GPIO_InitButton(S4);
  GPIO_InitButton(S6);
}