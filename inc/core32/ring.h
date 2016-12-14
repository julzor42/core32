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

#define BUFFER_PEEK(Buffer, Cursor)         Buffer[Cursor++]
#define BUFFER_POKE(Buffer, Cursor, Data)   Buffer[Cursor++] = Data
#define BUFFER_ROUND(Buffer, Cursor)        if (Cursor >= sizeof(Buffer)) Cursor = 0
#define PEEK_FUNC(Buffer, Cursor)           unsigned char c = BUFFER_PEEK(Buffer, Cursor); BUFFER_ROUND(Buffer, Cursor); return c
#define POKE_FUNC(Buffer, Cursor, c)        BUFFER_POKE(Buffer, Cursor, c); BUFFER_ROUND(Buffer, Cursor)

#define RBUFFER_CREATE(Name, Size) volatile unsigned char Name##_Buffer[Size]; \
  volatile unsigned int Name##_CursorR = 0; \
  volatile unsigned int Name##_CursorW = 0; \
  volatile unsigned int Name##_Size = 0

#define EXTERN_RINGBUFFER(Name) extern volatile unsigned char Name##_Buffer[]; \
  extern volatile unsigned int Name##_CursorR;				\
  extern volatile unsigned int Name##_CursorW;				\
  extern volatile unsigned int Name##_Size

#define RBUFFER_MAKE_PEEK(Name) inline unsigned char Peek_##Name() { PEEK_FUNC(Name##_Buffer, Name##_CursorR); Name##_Size--; }
#define RBUFFER_MAKE_POKE(Name) inline void Poke_##Name(unsigned char c) { POKE_FUNC(Name##_Buffer, Name##_CursorW, c); Name##_Size++; }

#define DECLARE_RINGBUFFER(Name, Size) RBUFFER_CREATE(Name, Size); \
  RBUFFER_MAKE_PEEK(Name); \
  RBUFFER_MAKE_POKE(Name)

#define RBUFFER_EMPTY(Name) (Name##_Size == 0)
#define RBUFFER_FULL(Name)  (Name##_Size == (sizeof(Name##_Buffer) / sizeof(Name##_Buffer[0])))