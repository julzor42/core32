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
#define OCxCON(x)           _SFR_KEY_PTR(OC, x, 0x00)
#define OCxCONCLR(x)        _SFR_KEY_CLR(OC, x, 0x00)
#define OCxCONSET(x)        _SFR_KEY_SET(OC, x, 0x00)
#define OCxR(x)             _SFR_KEY_PTR(OC, x, 0x10)
#define OCxRS(x)            _SFR_KEY_PTR(OC, x, 0x20)

//
// Functions
//
void    PWM_Initialize      (unsigned int Pin, unsigned int Timer, unsigned short Cycle);

#define PWM_SetDutyCycle(p, c) OCxRS(p) = (c)

#define OC_1      0
#define OC_2      1
#define OC_3      2
#define OC_4      3
#define OC_5      4
