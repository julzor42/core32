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

//
// DMA Channels
//
#define   DMA_0              0
#define   DMA_1              1
#define   DMA_2              2
#define   DMA_3              3
#define   DMA_4              4
#define   DMA_5              5
#define   DMA_6              6
#define   DMA_7              7
#define   DMA_8              8
#define   DMA_9              9
#define   DMA_10             10

//
// SFRs
//
#define   DCHxCON(x)        _SFR_KEY_PTR(DMA, x, 0x00)
#define   DCHxCONCLR(x)     _SFR_KEY_CLR(DMA, x, 0x00)
#define   DCHxCONSET(x)     _SFR_KEY_SET(DMA, x, 0x00)
#define   DCHxECON(x)       _SFR_KEY_PTR(DMA, x, 0x10)
#define   DCHxECONSET(x)    _SFR_KEY_SET(DMA, x, 0x10)
#define   DCHxECONCLR(x)    _SFR_KEY_CLR(DMA, x, 0x10)
#define   DCHxINT(x)        _SFR_KEY_PTR(DMA, x, 0x20)
#define   DCHxSSA(x)        _SFR_KEY_PTR(DMA, x, 0x30)
#define   DCHxDSA(x)        _SFR_KEY_PTR(DMA, x, 0x40)
#define   DCHxSSIZ(x)       _SFR_KEY_PTR(DMA, x, 0x50)
#define   DCHxDSIZ(x)       _SFR_KEY_PTR(DMA, x, 0x60)
#define   DCHxSPTR(x)       _SFR_KEY_PTR(DMA, x, 0x70)
#define   DCHxDPTR(x)       _SFR_KEY_PTR(DMA, x, 0x80)
#define   DCHxCSIZ(x)       _SFR_KEY_PTR(DMA, x, 0x90)
#define   DCHxCPTR(x)       _SFR_KEY_PTR(DMA, x, 0xA0)
#define   DCHxDAT(x)        _SFR_KEY_PTR(DMA, x, 0xB0)

#define   DMA_Enable()                DMACONbits.ON = 1
#define   DMA_Disable()               DMACONbits.ON = 0
#define   DMA_IsEnabled()             DMACONbits.ON

#define   DMA_EnableChannel(c)        DCHxCONSET(c) = DCHXCON_CHEN
#define   DMA_DisableChannel(c)       DCHxCONCLR(c) = DCHXCON_CHEN
#define   DMA_SetSource(c, a, s)      DCHxSSA(c) = KVA_TO_PA(a); DCHxSSIZ(c) = (s)
#define   DMA_SetDestination(c, a, s) DCHxDSA(c) = KVA_TO_PA(a); DCHxDSIZ(c) = (s)
#define   DMA_SetBlockSize(c, bs)     DCHxCSIZ(c) = (bs)

#define   DMA_EnableStartInterrupt(c) DCHxECONSET(c) = DCHXECON_SIRQEN
#define   DMA_ClearStartInterrupt(c)  DCHxECONCLR(c) = DCHXECON_SIRQEN

void      DMA_InitializeChannel       (unsigned int Channel, unsigned int Priority, unsigned int AutoRestart);
void      DMA_SetStartInterrupt       (unsigned int Channel, unsigned int Interrupt);
