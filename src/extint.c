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
#include <core32.h>
#include <core32/extint.h>

void INT_SetExternalInterrupt(unsigned int Int, unsigned int Polarity, unsigned int Priority, unsigned int SubPriority)
{
  INT_DisableExternalInterrupt(Int);
  INT_ClearExternalInterrupt(Int);

  switch (Int)
  {
    case INT_1:
    INTCONbits.INT1EP = Polarity;
    IPC1bits.INT1IP   = Priority;
    IPC1bits.INT1IS   = SubPriority;
    break;
  }

  INT_EnableExternalInterrupt(Int);
}

void INT_SetExternalInterruptState(unsigned int Int, unsigned int Enabled)
{
  switch (Int)
  {
    case INT_1: IEC0bits.INT1IE = Enabled; break;
  }
}

void INT_ClearExternalInterrupt(unsigned int Int)
{
  switch (Int)
  {
    case INT_1: IFS0bits.INT1IF = 0; break;
  }
}
