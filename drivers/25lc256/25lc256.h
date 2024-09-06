/*
  MIT License

  Copyright (c) 2024 Julien Delmotte

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
#ifndef _25LC256_H_
#define _25LC256_H_

#define SRAM_MODE_BYTE  0x00
#define SRAM_MODE_SEQ   0x40
#define SRAM_MODE_PAGE  0x80

void    SRAM_Initialize (unsigned int Port, unsigned int RamFreq, unsigned int Mode);
void    SRAM_SetMode    (unsigned int Port, unsigned char Mode);
void    SRAM_Read       (unsigned int Port, unsigned int Address, unsigned char* pData, unsigned int Length);
void    SRAM_Write      (unsigned int Port, unsigned int Address, const unsigned char* pData, unsigned int Length);

/*
 Usage:
 * SRAM_Initialize(SPI_3, 10000000, SRAM_MODE_SEQ);
 * SRAM_Write(SPI_3, 0, "Hello", 6);
 * char tmp[32] = {0};
 * SRAM_Read(SPI_3, 0, tmp, 6); 
 */

#endif /* _25LC256_H_ */
