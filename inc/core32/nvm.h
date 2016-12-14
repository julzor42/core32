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

#define PAGE_SIZE               1024            // # of 32-bit Instructions per Page
#define BYTE_PAGE_SIZE          (4 * PAGE_SIZE) // Page size in Bytes
#define ROW_SIZE                128             // # of 32-bit Instructions per Row
#define BYTE_ROW_SIZE           (4 * ROW_SIZE)  // # Row size in Bytes
#define NUM_ROWS_PAGE           8               //Number of Rows per Page 

#define NVMOP_WORD_PGM          0x4001          // Word program operation
#define NVMOP_PAGE_ERASE        0x4004          // Page erase operation
#define NVMOP_ROW_PGM           0x4003          // Row program operation
#define NVMOP_NOP               0x4000          // NOP operation

#define                                   NVM_HasError()    (NVMCON & (_NVMCON_WRERR_MASK | _NVMCON_LVDERR_MASK))
#define                                   NVM_SetAddress(a) NVMADDR = KVA_TO_PA((unsigned int)(a))
#define                                   NVM_SetData(d)    NVMDATA = (d)
#define                                   NVM_SetSrcAddr(a) NVMSRCADDR = KVA_TO_PA((unsigned int)(a))
unsigned int __attribute__((nomips16))    NVM_Operation     (unsigned int Operation);
unsigned int                              NVM_ErasePage     (void* Address);
unsigned int                              NVM_WriteWord     (void* Address, unsigned int Data);
unsigned int                              NVM_WriteRow      (void* Address, void* Data);
unsigned int                              NVM_ClearError    ();
