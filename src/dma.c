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
#include <core32/dma.h>

void DMA_InitializeChannel(unsigned int Channel, unsigned int Priority, unsigned int AutoRestart)
{
  DCHxCONCLR(Channel) = 0b11;
  DCHxCONSET(Channel) = Priority & 0b11;
  
  if (AutoRestart)
    DCHxCONSET(Channel) = DCHXCON_CHAEN;
  else
    DCHxCONCLR(Channel) = DCHXCON_CHAEN;
}

void DMA_SetStartInterrupt(unsigned int Channel, unsigned int Interrupt)
{
  // Set interrupt source
  DCHxECONCLR(Channel) = 0x0000ff00;
  DCHxECONSET(Channel) = (Interrupt & 0xffff) << 8;
  
  DMA_EnableStartInterrupt(Channel);
}

#endif