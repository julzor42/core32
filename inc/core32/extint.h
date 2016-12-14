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

#define             INT_0 0
#define             INT_1 1
#define             INT_2 2
#define             INT_3 3
#define             INT_4 4
#define             INT_5 5

void                INT_SetExternalInterrupt(unsigned int Int, unsigned int Polarity, unsigned int Priority, unsigned int SubPriority);
void                INT_SetExternalInterruptState(unsigned int Int, unsigned int Enabled);
void                INT_ClearExternalInterrupt(unsigned int Int);

#define             INT_EnableExternalInterrupt(Int)   INT_SetExternalInterruptState(Int, ENABLED)
#define             INT_DisableExternalInterrupt(Int)  INT_SetExternalInterruptState(Int, DISABLED)