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
#include <core32/adc.h>

#ifdef __PIC32MX__

void ADC_Initialize()
{
  AD1CON1 = 0;
  AD1CON1bits.SSRC = 0b111; // Auto convert after end of sampling
  // Tad length, must be at least than 65ns (= Tpb * 2 * (ADCS + 1))
  AD1CON3bits.ADCS = 2; // Tpb * 2 * (2 + 1) = 75ns
  AD1CON3bits.SAMC = 2; // Tad count, Sampling must be at least 132ns
  AD1CON1bits.ON = 1;   // Enable ADC
}

unsigned int ADC_Read()
{
  AD1CON1bits.DONE = 0;
  AD1CON1bits.SAMP = 1;
  System_DelayMs(10);
  AD1CON1bits.SAMP = 0;
  System_DelayMs(10);  
  while (!AD1CON1bits.DONE)
    ;
  System_DelayMs(10);
  AD1CON1bits.DONE = 1;    

  return ADC1BUF0;
}

#endif