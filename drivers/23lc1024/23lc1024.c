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
#include <23lc1024/23lc1024.h>

#define SRAM_READ    0x03
#define SRAM_WRITE   0x02
#define SRAM_REGR    0x05
#define SRAM_REGW    0x01

#ifndef SRAM_TRIS
#error SRAM_TRIS not defined and is required to access the SRAM chip
#endif

#ifndef SRAM_CS
#error SRAM_CS not defined and is required to access the SRAM chip
#endif

void SRAM_Initialize(unsigned int Port, unsigned int RamFreq, unsigned int Mode)
{
  SPI_Initialize(Port, RamFreq, 1, 1);
  SRAM_TRIS   = 0;
  SRAM_CS     = 1;
  SRAM_SetMode(Port, Mode);
}

void SRAM_SetMode(unsigned int Port, unsigned char Mode)
{
  SRAM_CS = 0;
  SPI_Data(Port, SRAM_REGW);
  SPI_Data(Port, Mode);
  SRAM_CS = 1;
}

static inline void _SRAM_SendAddress(unsigned int Port, unsigned int Address)
{
  SPI_Data(Port, Address >> 16);
  SPI_Data(Port, Address >> 8);
  SPI_Data(Port, Address);
}

void SRAM_Write(unsigned int Port, unsigned int Address, const unsigned char* pData, unsigned int Length)
{   
  SRAM_CS = 0;
  SPI_Data(Port, SRAM_WRITE);
  _SRAM_SendAddress(Port, Address);
  while (Length--)
    SPI_Data(Port, *pData++);
  SRAM_CS = 1;    
}

void SRAM_Read(unsigned int Port, unsigned int Address, unsigned char* pData, unsigned int Length) 
{
  SRAM_CS = 0;
  SPI_Data(Port, SRAM_READ);
  _SRAM_SendAddress(Port, Address);
  while (Length--)
    *pData++ = SPI_Data(Port, 0x00);
  SRAM_CS = 1;
}