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
#include <p32xxxx.h>
#include <core32.h>

#ifdef USE_BASECONF
//
// Base configuration (SYSCLK = 80Mhz, PBCLK = SYSCLK)
//
#pragma config POSCMOD  = XT
#pragma config FNOSC    = PRIPLL
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL  = MUL_20
#pragma config FPLLODIV = DIV_1
#pragma config FPBDIV   = DIV_1
#endif

void System_Initialize()
{
  unsigned int val;
  
  BMXCONCLR = _BMXCON_BMXWSDRM_MASK;
  
#ifdef _PCACHE
  CHECONbits.PFMWS  = 2;   // 4 wait states (1 wait state each 20 Mhz)
  CHECONbits.PREFEN = 3;   // Enable predictive prefetch for both regions
#endif
  
  // Make KSEG0 cacheable
  unsigned int config;
  config          = _mfc0 (_CP0_CONFIG, _CP0_CONFIG_SELECT);
  config         &= ~ _CP0_CONFIG_K0_MASK;
  config         |= 3 << _CP0_CONFIG_K0_POSITION;
  _mtc0 (_CP0_CONFIG, _CP0_CONFIG_SELECT, config);
  
  // Configure interrupts
#if defined(SYSTEM_INT_SINGLE) || defined(SYSTEM_INT_MULTI)
  // set the CP0 cause IV bit high
  asm volatile("mfc0 %0,$13" : "=r"(val));
  val |= 0x00800000;
  asm volatile("mtc0 %0,$13" : "+r"(val));
     
#ifdef SYSTEM_INT_MULTI
  INTCONbits.MVEC = 1;
#endif
     
  val = 0;
  asm volatile("ei %0" : "=r"(val));
#endif
  
  // Disable JTAG
  DDPCONbits.JTAGEN = 0;

  // Setup peripheral clock
  System_SetPBDiv(SYSTEM_PBDIV);

  // Setup core timer
  _CP0_SET_COMPARE(0xffffffff);
  _CP0_SET_COUNT  (0x00000000);
}

void System_SetPBDiv(unsigned int PbDiv)
{
  System_Unlock();
  switch (PbDiv)
  {
    case 1: OSCCONbits.PBDIV = 0b00; break;
    case 2: OSCCONbits.PBDIV = 0b01; break;
    case 4: OSCCONbits.PBDIV = 0b10; break;
    case 8: OSCCONbits.PBDIV = 0b11; break;
  }
  System_Lock();
}

void System_Idle()
{
  OSCCONCLR = 0x10;
  asm volatile("wait");
}

void System_Sleep()
{
  OSCCONSET = 0x10;
  asm volatile("wait");
}

void System_DelayUs(unsigned int Delay)
{
  unsigned int nStart = _CP0_GET_COUNT();
  while ((_CP0_GET_COUNT() - nStart) < Delay * CORE_US);
}

unsigned int __attribute__((nomips16)) System_EnableInterrupts()
{
    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
    return status;
}

unsigned int __attribute__((nomips16)) System_DisableInterrupts()
{
    unsigned int status = 0;
    asm volatile("di    %0" : "=r"(status));
    return status;
}

void __attribute__((nomips16)) System_RestoreInterrupts(unsigned int Status)
{
    if (Status & 0x00000001)
        asm volatile("ei");
    else
        asm volatile("di");
}

void System_Reset()
{
  int t;
  
  SYSKEY = 0;
  SYSKEY = 0xAA996655;
  SYSKEY = 0x556699AA;
  
  RSWRSTSET = 1;
  t = RSWRST;
  
  while (1)
    ;

  t++;
}

void System_Unlock()
{
  SYSKEY = 0x0;
  SYSKEY = 0xAA996655;
  SYSKEY = 0x556699AA;
}

void System_Lock()
{
  SYSKEY = 0x0;  
}

#ifdef PIC32MX2
void System_UnlockPPS()
{
  System_Unlock();
  CFGCONbits.IOLOCK = 0;
}

void System_LockPPS()
{
  CFGCONbits.IOLOCK = 1;
  System_Lock();
} 
#endif
