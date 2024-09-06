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
#include <core32/timers.h>

void Timer_Initialize(unsigned int Timer, unsigned int Prescaler, unsigned short Period)
{
  // Disable and reset timer
  TxCON(Timer) = 0;
    
  if (Timer == TIMER_1)
  {
    switch (Prescaler)
    {
      case 1:   break;
      case 8:   TxCONSET(Timer) = 1 << 4; break;
      case 64:  TxCONSET(Timer) = 2 << 4; break;
      case 256: TxCONSET(Timer) = 3 << 4; break;
    }
  }
  else
  {
    switch (Prescaler)
    {
      case 1:   break;
      case 2:   TxCONSET(Timer) = 1 << 4; break;
      case 4:   TxCONSET(Timer) = 2 << 4; break;
      case 8:   TxCONSET(Timer) = 3 << 4; break;
      case 16:  TxCONSET(Timer) = 4 << 4; break;
      case 32:  TxCONSET(Timer) = 5 << 4; break;
      case 64:  TxCONSET(Timer) = 6 << 4; break;
      case 256: TxCONSET(Timer) = 7 << 4; break;
    }
  }
  
  // Clear count
  Timer_Write(Timer, 0);
  Timer_SetPeriod(Timer, Period);
  
  Timer_Enable(Timer);
}

void Timer_Wait(unsigned int Timer, unsigned int Cycles)
{
  unsigned int Now = Timer_Read(Timer);
  while ((Timer_Read(Timer) - Now) < Cycles);
}

void Timer_ClearInterrupt(unsigned int Timer)
{
  switch (Timer)
  {
    case TIMER_1: IFS0bits.T1IF = 0; break;
    case TIMER_2: IFS0bits.T2IF = 0; break;
    case TIMER_3: IFS0bits.T3IF = 0; break;
    case TIMER_4: IFS0bits.T4IF = 0; break;
    case TIMER_5: IFS0bits.T5IF = 0; break;
  }
}

void Timer_EnableInterrupt(unsigned int Timer, unsigned int Enabled)
{
  switch (Timer)
  {
    case TIMER_1: IEC0bits.T1IE = Enabled; break;
    case TIMER_2: IEC0bits.T2IE = Enabled; break;
    case TIMER_3: IEC0bits.T3IE = Enabled; break;
    case TIMER_4: IEC0bits.T4IE = Enabled; break;
    case TIMER_5: IEC0bits.T5IE = Enabled; break;
  }
}

void Timer_SetInterrupt(unsigned int Timer, unsigned int Enabled, unsigned int Priority, unsigned int SubPriority)
{
  Timer_EnableInterrupt(Timer, DISABLED);

  switch (Timer)
  {
    case TIMER_1:
      IPC1bits.T1IP = Priority;
      IPC1bits.T1IS = SubPriority;
      break;
      
    case TIMER_2:
      IPC2bits.T2IP = Priority;
      IPC2bits.T2IS = SubPriority;
      break;
      
    case TIMER_3:
      IPC3bits.T3IP = Priority;
      IPC3bits.T3IS = SubPriority;
      break;
      
    case TIMER_4:
      IPC4bits.T4IP = Priority;
      IPC4bits.T4IS = SubPriority;
      break;
      
    case TIMER_5:
      IPC5bits.T5IP = Priority;
      IPC5bits.T5IS = SubPriority;
      break;
  }
  
  Timer_ClearInterrupt(Timer);
  Timer_EnableInterrupt(Timer, Enabled);
}

#endif