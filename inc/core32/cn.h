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

#define CN_SetPins(Pins)	      CNEN = (Pins)
#define CN_SetPullUps(Pins)	    CNPUE = (Pins)
#define CN_Enable()		          CNCONbits.ON = 1
#define CN_Disable()            CNCONbits.ON = 0
#define CN_EnableInterrupt()	  IEC1bits.CNIE = 1
#define CN_DisableInterrupt()   IEC1bits.CNIE = 0
#define CN_ClearInterrupt()	    IFS1bits.CNIF = 0
#define CN_SetPriority(p)	      IPC6bits.CNIP = (p)
#define CN_SetSubPriority(p)	  IPC6bits.CNIS = (p)

void    CN_SetInterrupt(unsigned int Priority, unsigned int SubPriority);

