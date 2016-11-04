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
#ifndef _TASK_H_
#define _TASK_H_

//
// Task handler type
//
struct Task_s;
typedef void (*TaskHandler)(struct Task_s*);

typedef struct Task_s
{
    unsigned int State;
    TaskHandler  Handler;
    TaskHandler  Replace;
    void*        Data;
    unsigned int Events;
    
    union
    {
      struct // Delay
      {
        unsigned int DelayNextState;
        unsigned int DelayStart;
        unsigned int Delay;
      };
      struct // Wait address
      {
        unsigned int           WaitNextState;
        volatile unsigned int* WaitAddress;
        unsigned int           WaitMask;
      };
    };

}   Task_t;

enum TASK_STATE
{
    // Base states
    TASK_START   = 0,
    TASK_IDLE,
    TASK_EXIT,
    
    // Common states
    TASK_DELAY   = 0xffff0000,
    TASK_WAITMASK,
    TASK_EXITING,
    TASK_AUTO    = -1
};

void        Task_Initialize         ();
Task_t*     Task_Create             (TaskHandler Handler, void* Data);
Task_t*     Task_FindFree           ();
void        Task_ProcessAll         ();
void        Task_Loop               ();
void        Task_Process            (Task_t* pTask);

void        Task_SetDelay           (Task_t* pTask, unsigned int DelayUs, unsigned int NextState);
void        Task_WaitMask           (Task_t* pTask, unsigned int* pAddress, unsigned int Mask, unsigned int NextState);
void        Task_Exit               (Task_t* pTask, TaskHandler Replace);

#define     Task_SetState(t, s)     t->State = (s)
#define     Task_GetState(t)        (t->State)
#define     Task_Switch(t)          switch (t->State)
#define     Task_GetData(t, type)   ((type)(t->Data)
#define     Task_SetData(t, obj)    t->Data = (obj)

#define     Task_Sleep(t, delay)    Task_SetDelay(t, delay, TASK_AUTO)

#define     Task_WaitEvent(t, i, n) Task_WaitMask(t, &task->Events, 1 << (i))
#define     Task_SetEvent(t, i)     t->Events |= 1 << (i)
#define     Task_ClearEvent(t, i)   t->Events &= ~(1 << (i))

#endif /* _TASK_H_ */
