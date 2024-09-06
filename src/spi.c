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
#include <core32/spi.h>

void SPI_Initialize(unsigned int Port, unsigned int Freq, unsigned int Master, unsigned int Mode)
{
  // Disable and reset SPI
  SPIxCON(Port) = 0;
  
  PBDIV1_CYCLE_WAIT();
  
  if (Master)       SPIxCONSET(Port) = SPICON_MSTEN;
  if (Mode & 0x01)  SPIxCONSET(Port) = SPICON_CKE; // CPHA
  if (Mode & 0x02)  SPIxCONSET(Port) = SPICON_CKP; // CPOL
  
  SPIxBRG(Port) = PBCLK / (2 * Freq) - 1;
  
  SPI_Enable(Port);
}

unsigned int SPI_Data(unsigned int Port, unsigned int Data)
{
  SPIxBUF(Port) = Data;
  while (!(SPIxSTAT(Port) & SPISTAT_SPIRBF));
  return SPIxBUF(Port);
}

void SPI_Buffer(unsigned int Port, unsigned char* pSend, unsigned char* pRecv, unsigned int Length)
{
  unsigned int n;
  
  for (n = 0; n < Length; n++)
  {
    pRecv[n] = SPI_Data(Port, pSend[n]);
  }
}

void SPI_Print(unsigned int Port, unsigned char* Message)
{
  while (*Message)
  {
    SPI_Data(Port, *Message++);
  }
}

#endif