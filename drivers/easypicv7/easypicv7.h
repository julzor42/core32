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
#ifndef _EASYPICV7_H_
#define _EASYPICV7_H_

#define BOARD_NAME    "EasyPIC Fusion v7"
#define BOARD_EPF7

#define CS1_TRIS      _TRISC2
#define CS2_TRIS      _TRISC4

#define CS1_ENABLE()  _LATC2 = 0
#define CS1_DISABLE() _LATC2 = 1

#define CS2_ENABLE()  _LATC4 = 0
#define CS2_DISABLE() _LATC4 = 1

#define EPF7_SPI       SPI_3

#define EPF7_UART_A    UART_2
#define EPF7_UART_B    UART_5

void    Board_Startup();

#endif /* _EASYPICV7_H_ */
