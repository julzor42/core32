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
#ifndef _ADC_H_
#define _ADC_H_

#define       ADC_Enable()            AD1CONbits.ON = 1
#define       ADC_Disable()           AD1CONbits.ON = 0
#define       ADC_SetDigital(pins)    AD1PCFGSET  = (pins)
#define       ADC_SetAnalog(pins)     AD1PCFGCLR  = (pins)
#define       ADC_SetChannel(c)       AD1CHS      = ((c) << 16)
#define       ADC_AllDigital()        ADC_SetDigital(0xffff)

void          ADC_Initialize          ();
unsigned int  ADC_Read                ();

#endif /* _ADC_H_ */