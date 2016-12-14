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

#define BASEADDRESS_SPI     0xBF805800
#define SPIxCON_BASE(x)     _SFR_ADDR(BASEADDRESS_SPI, 0x200, x)

//
// SFRs
//
#define SPIxBUF(x)          _SFR(SPIxCON_BASE(x) + 0x20)
#define SPIxBRG(x)          _SFR(SPIxCON_BASE(x) + 0x30)
#define SPIxCON(x)          _SFR(SPIxCON_BASE(x))
#define SPIxCONCLR(x)       _SFR_CLR(SPIxCON_BASE(x))
#define SPIxCONSET(x)       _SFR_SET(SPIxCON_BASE(x))
#define SPIxSTAT(x)         _SFR(SPIxCON_BASE(x) + 0x10)
#define SPIxSTATCLR(x)      _SFR_CLR(SPIxCON_BASE(x) + 0x10)
#define SPIxSTATSET(x)      _SFR_SET(SPIxCON_BASE(x) + 0x10)

//
// SPI Ports
//
#define SPI_3               0
#define SPI_2               1
#define SPI_4               2
#define SPI_1               3

//
// Macros
//
#define         SPI_Enable(port)    SPIxCONSET(port) = SPICON_ON
#define         SPI_Disable(port)   SPIxCONCLR(port) = SPICON_ON
#define         SPI_IsEnabled(port) (SPIxCON(port) & SPICON_ON)

//
// Functions
//
void            SPI_Initialize      (unsigned int Port, unsigned int Freq, unsigned int Master, unsigned int Mode);
unsigned int    SPI_Data            (unsigned int Port, unsigned int Data);
void            SPI_Buffer          (unsigned int Port, unsigned char* pSend, unsigned char* pRecv, unsigned int Length);
void            SPI_Print           (unsigned int Port, unsigned char* Message);
