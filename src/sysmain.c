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

// Prototypes
void __attribute__((weak)) Program(Task_t*);
void __attribute__((weak)) Board_Startup();

int __attribute__((weak)) main()
{
  if (Board_Startup)
  {
    Board_Startup();
  }
  else
  {
    System_Initialize();

    #ifdef __PIC32MX__
      #ifdef UART_CONSOLE
      UART_Initialize(UART_CONSOLE, UART_CONSOLE_SPEED, UART_READWRITE);
      #endif
    #endif
  }

  Task_Initialize();
  if (Program)
    Task_Create(Program, NULL);
  Task_Loop();

  return 0;
}
