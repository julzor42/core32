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

#ifdef TASK_console

#include <core32.h>
#include <stdint.h>

typedef void (*CONSOLE_HANDLER)(const char*, uint32_t);

#ifndef CONSOLE_COMMAND_MAXLEN
#define CONSOLE_COMMAND_MAXLEN  64
#endif

typedef struct Console_s
{
    uint32_t        Port;
    CONSOLE_HANDLER Handler;
    char            Command[CONSOLE_COMMAND_MAXLEN];
    uint32_t        Length;
    
    union
    {
        struct
        {
          int       Echo:1;
          int       Validate:1;
        };
        uint32_t    Flags;
    };

} Console_t;

void Console_Attach(uint32_t Port, CONSOLE_HANDLER Handler, Console_t* pConsole);

#endif
