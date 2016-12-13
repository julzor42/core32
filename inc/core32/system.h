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
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//
// Macros
//
#define PBCLK                  (SYSTEM_FREQ / SYSTEM_PBDIV)

//
// Special function registers
//
#define _SFR(addr)             *((volatile unsigned int*)(addr))
#define _SFR_CLR(addr)         _SFR((addr) + 0x04)
#define _SFR_SET(addr)         _SFR((addr) + 0x08)
#define _SFR_INV(addr)         _SFR((addr) + 0x0c)
#define _SFR_ADDR(addr, sz, n) ((addr) + ((sz) * (n)))
#define _SFR_TYPE(type, addr)  ((volatile type*)(addr))

//
// Tools
//
#define BUFFER_PEEK(Buffer, Cursor)         Buffer[Cursor++]
#define BUFFER_POKE(Buffer, Cursor, Data)   Buffer[Cursor++] = Data
#define BUFFER_ROUND(Buffer, Cursor)        if (Cursor >= sizeof(Buffer)) Cursor = 0
#define PEEK_FUNC(Buffer, Cursor)           unsigned char c = BUFFER_PEEK(Buffer, Cursor); BUFFER_ROUND(Buffer, Cursor); return c
#define POKE_FUNC(Buffer, Cursor, c)        BUFFER_POKE(Buffer, Cursor, c); BUFFER_ROUND(Buffer, Cursor)

//
// Functions
//
void          System_Initialize         ();
void          System_Reset              ();
void	        System_Idle		            ();
void          System_Sleep              ();
void          System_DelayUs            (unsigned int Delay);
void          System_UnlockPPS          ();
void          System_LockPPS            ();
void          System_Unlock             ();
void          System_Lock               ();
unsigned int  System_EnableInterrupts   ();
unsigned int  System_DisableInterrupts  ();
void          System_RestoreInterrupts  (unsigned int Status);
void          System_SetPBDiv           (unsigned int PbDiv);

#define System_DelayMs(ms)	   System_DelayUs((ms) * 1000)
#define System_TimeStart(var)  (var) = _CP0_GET_COUNT()
#define System_TimeEnd(var)    (var) = (_CP0_GET_COUNT() - (var)) / CORE_US
#define System_TimeNow()       (_CP0_GET_COUNT() / CORE_US)

#endif /* _SYSTEM_H_ */
