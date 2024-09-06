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
#ifdef __PIC32MX__

#include <core32.h>
#include <core32/oc.h>

void PWM_Initialize(unsigned int Pin, unsigned int Timer, unsigned short Cycle)
{
  // Disable and reset OC
  OCxCON(Pin) = 0;
    
  // Set PWM mode
  OCxCONSET(Pin) = 0b110;
    
  // Select timer
  if (Timer == TIMER_2) OCxCONCLR(Pin) = 1 << 3;    // Timer2
  else                  OCxCONSET(Pin) = 1 << 3;    // Timer3
    
  OCxRS(Pin) = Cycle;
    
  // Enable OC
  OCxCONSET(Pin) = OCCON_ON;
}

#endif