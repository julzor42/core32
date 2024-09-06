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
#include <core32/nvm.h>
#include <core32/dma.h>

unsigned int __attribute__((nomips16)) NVM_Operation(unsigned int Operation)
{
  unsigned int Status;
  unsigned int DmaStatus;
  
  Status = System_DisableInterrupts();
  DmaStatus = DMA_IsEnabled();  
  
  // Enable write/erase
  NVMCON    = NVMCON_WREN | Operation;
  System_DelayUs(7);
  
  NVMKEY    = 0xAA996655;
  NVMKEY    = 0x556699AA;
  NVMCONSET = NVMCON_WR;
  
  while (NVMCON & NVMCON_WR);
  
  // Disable write/erase
  NVMCONCLR = NVMCON_WREN;
  
  if (DmaStatus)
    DMA_Enable();

  System_RestoreInterrupts(Status);
  
  return NVM_HasError();
}

unsigned int NVM_ErasePage(void* Address)
{
  NVM_SetAddress(Address);  
  return NVM_Operation(NVMOP_PAGE_ERASE);
}

unsigned int NVM_WriteWord(void* Address, unsigned int Data)
{
  NVM_SetAddress(Address);
  NVM_SetData(Data);
  
  return NVM_Operation(NVMOP_WORD_PGM);
}

unsigned int NVM_WriteRow(void* Address, void* Data)
{
  NVM_SetAddress(Address);
  NVM_SetSrcAddr(Data);
  
  return NVM_Operation(NVMOP_ROW_PGM);
}

#endif