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

typedef struct              Port_s
{         
  unsigned int              TRIS;
  unsigned int              TRISCLR;
  unsigned int              TRISSET;
  unsigned int              TRISINV;
         
  unsigned int              PORT;
  unsigned int              PORTCLR;
  unsigned int              PORTSET;
  unsigned int              PORTINV;
          
  unsigned int              LAT;
  unsigned int              LATCLR;
  unsigned int              LATSET;
  unsigned int              LATINV;
              
  unsigned int              ODC;
  unsigned int              ODCCLR;
  unsigned int              ODCSET;
  unsigned int              ODCINV;
}                           Port_t;

typedef volatile Port_t*    VPort;

#define PORT(x)             _SFR_KEY_TYPE(Port_t, GPIO, x)
#define PortA               PORT(0)
#define PortB               PORT(1)
#define PortC               PORT(2)
#define PortD               PORT(3)
#define PortE               PORT(4)
#define PortF               PORT(5)
#define PortG               PORT(6)

#define PIN_0               BIT_0
#define PIN_1               BIT_1
#define PIN_2               BIT_2
#define PIN_3               BIT_3
#define PIN_4               BIT_4
#define PIN_5               BIT_5
#define PIN_6               BIT_6
#define PIN_7               BIT_7
#define PIN_8               BIT_8
#define PIN_9               BIT_9
#define PIN_10              BIT_10
#define PIN_11              BIT_11
#define PIN_12              BIT_12
#define PIN_13              BIT_13
#define PIN_14              BIT_14
#define PIN_15              BIT_15
#define PINS_L              0x00ff
#define PINS_H              0xff00
#define PINS_ALL            0xffff

#define GPIO_SetOutput(p, b)   p->TRISCLR = (b)
#define GPIO_SetInput(p, b)    p->TRISSET = (b)
#define GPIO_Write(p, d)       p->LAT = (d)
#define GPIO_Read(p)           (p->PORT)
#define GPIO_GetBits(p, b)     (p->PORT & (b))
#define GPIO_SetBits(p, b)     p->LATSET = (b)
#define GPIO_CheckBits(p, b)   (GPIO_GetBits(p, b) == (b))
#define GPIO_ClearBits(p, b)   p->LATCLR = (b)
#define GPIO_ToggleBits(p, b)  p->LATINV = (b)

#define GPIO_GetButton(key)    GPIO_GetBits(BUTTON_##key##_PORT, BUTTON_##key##_PIN)
#define GPIO_InitButton(key)   GPIO_SetInput(BUTTON_##key##_PORT, BUTTON_##key##_PIN)
