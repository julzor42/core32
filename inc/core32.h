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
#ifndef _CORE32_H_
#define _CORE32_H_

//
// System headers
//
#include <p32xxxx.h>
#include <sys/kmem.h>
#include <sys/attribs.h>

#include <core32/macros.h>

// User configuration file
#include <core32conf.h>

#include <core32/system.h>

//
// Macros
//
#define CORE_US     (SYSTEM_FREQ / 2000000)

#if SYSTEM_PBDIV == 1
  // From datasheet: When using the 1:1 PBCLK divisor,
  // the software should not read/write the peripheral SFR
  // in the SYSCLK cycle immediatly following the instruction
  // that clears the module's ON bit
# define PBDIV1_CYCLE_WAIT()    _nop()
#else
# define PBDIV1_CYCLE_WAIT()
#endif

//
// Features
//
#include <core32/tasks.h>
#include <core32/timers.h>
#include <core32/gpio.h>
#include <core32/oc.h>
#include <core32/uart.h>
#include <core32/spi.h>
#include <core32/i2c.h>
#include <core32/nvm.h>
#include <core32/adc.h>
#include <core32/dma.h>
#include <core32/extint.h>
#include <core32/cn.h>

#endif /* _CORE32_H_ */
