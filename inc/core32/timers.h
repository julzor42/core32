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
#define TMRx(x)             _SFR_KEY_PTR(TIMER, x, 0x10)
#define PRx(x)              _SFR_KEY_PTR(TIMER, x, 0x20)
#define TxCON(x)            _SFR_KEY_PTR(TIMER, x, 0x00)
#define TxCONCLR(x)         _SFR_KEY_CLR(TIMER, x, 0x00)
#define TxCONSET(x)         _SFR_KEY_SET(TIMER, x, 0x00)

#define TXCON_TCS           1 << 1
#define TXCON_TSYNC         1 << 2
#define TXCON_T32           1 << 3
#define TXCON_TCKPS         // TODO
#define TXCON_TGATE         1 << 7
#define TXCON_TWIP          1 << 11
#define TXCON_TWDIS         1 << 12
#define TXCON_SIDL          1 << 13
#define TXCON_FRZ           1 << 14
#define TXCON_ON            1 << 15

//
// Timers
//
#define TIMER_1             0
#define TIMER_2             1
#define TIMER_3             2
#define TIMER_4             3
#define TIMER_5             4

//
// Macros
//
#define Timer_Enable(timer)             TxCONSET(timer) = TXCON_ON
#define Timer_Disable(timer)            TxCONCLR(timer) = TXCON_ON
#define Timer_IsEnabled(timer)          (TxCON(timer) & TXCON_ON)
#define Timer_SetPeriod(timer, period)  PRx(timer) = (period)
#define Timer_Write(timer, value)       TMRx(timer) = (value)
#define Timer_Read(timer)               (TMRx(timer))

//
// Functions
//
void    Timer_Initialize    (unsigned int Timer, unsigned int Prescaler, unsigned short Period);
void    Timer_Wait          (unsigned int Timer, unsigned int Cycles);
void    Timer_SetInterrupt  (unsigned int Timer, unsigned int Enabled, unsigned int Priority, unsigned int SubPriority);
void    Timer_EnableInterrupt(unsigned int Timer, unsigned int Enabled);
void    Timer_ClearInterrupt(unsigned int Timer);
