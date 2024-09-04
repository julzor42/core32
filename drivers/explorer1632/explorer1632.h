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
#ifndef _EXPLORER1632_H_
#define _EXPLORER1632_H_

#define BOARD_NAME    "Explorer 16/32"
#define BOARD_EX1632

#define CS1_TRIS      _TRISG9
#define CS2_TRIS      _TRISD9

#define CS1_ENABLE()  _LATG9 = 0
#define CS1_DISABLE() _LATG9 = 1

#define CS2_ENABLE()  _LATD9 = 0
#define CS2_DISABLE() _LATD9 = 1

#define EX1632_SPI_A  SPI_2
#define EX1632_SPI_B  SPI_1

#define EX1632_UART_A UART_1
#define EX1632_UART_B UART_2

#define EX1632_RST_A      _LATF3
#define EX1632_RST_B      _LATE9
#define EX1632_RST_A_TRIS _TRISF3
#define EX1632_RST_B_TRIS _TRISE9

#define BUTTON_S3_PORT    PortD
#define BUTTON_S3_PIN     PIN_6
#define BUTTON_S4_PORT    PortD
#define BUTTON_S4_PIN     PIN_13
#define BUTTON_S5_PORT    PortA
#define BUTTON_S5_PIN     PIN_7
#define BUTTON_S6_PORT    PortD
#define BUTTON_S6_PIN     PIN_7

void    Board_Startup();
void    EX1632_InitLeds();

#endif /* _EXPLORER1632_H_ */
