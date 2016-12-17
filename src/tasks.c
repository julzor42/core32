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
#include <core32/tasks.h>

#include <string.h>

#ifndef TASK_MAX
#define TASK_MAX 8
#endif

Task_t g_Tasks[TASK_MAX];

void Task_Initialize()
{
  unsigned int nTask;

  for (nTask = 0; nTask < TASK_MAX; nTask++)
  {
    memset(&g_Tasks[nTask], 0, sizeof(g_Tasks[0]));
  }
}

Task_t *Task_FindFree()
{
  unsigned int nTask;

  for (nTask = 0; nTask < TASK_MAX; nTask++)
  {
    g_Tasks[nTask].Id = nTask;
    if (g_Tasks[nTask].Handler == 0)
      return &g_Tasks[nTask];
  }

  return 0;
}

Task_t *Task_Create(TaskHandler Handler, void *Data)
{
  Task_t *pTask;

  pTask = Task_FindFree();

  if (pTask != 0)
  {
    memset(pTask, 0, sizeof(Task_t));
    pTask->Handler = Handler;
    pTask->Data = Data;
  }

  return pTask;
}

__attribute__((weak)) void Task_OnSleepEnter() {}
__attribute__((weak)) void Task_OnSleepExit() {}
__attribute__((weak)) void Task_OnIdleEnter() {}
__attribute__((weak)) void Task_OnIdleExit() {}

void Task_ProcessAll()
{
  unsigned int nTask;
  Task_t *pTask;

  unsigned int AllowIdle = 1;
  unsigned int AllowSleep = 1;

  for (nTask = 0; nTask < TASK_MAX; nTask++)
  {
    pTask = &g_Tasks[nTask];
    if (pTask->Handler != 0)
    {
      Task_Process(pTask);
      g_Tasks[nTask].Handler(pTask);

      if (pTask->State == TASK_START)
        pTask->State = TASK_IDLE;
      if (pTask->State == TASK_EXIT)
      {
        pTask->State = TASK_START;
        pTask->Handler = pTask->Replace;
      }
      if (pTask->State == TASK_EXITING)
        pTask->State = TASK_EXIT;

      AllowIdle &= pTask->CanIdle;
      AllowSleep &= pTask->CanSleep;
    }
  }

  if (AllowSleep)
  {
    Task_OnSleepEnter();
    System_Sleep();
    Task_OnSleepExit();
  }
  else if (AllowIdle)
  {
    Task_OnIdleEnter();
    System_Idle();
    Task_OnIdleExit();
  }
}

void Task_Loop()
{
  while (1)
    Task_ProcessAll();
}

void Task_Exit(Task_t *pTask, TaskHandler NewHandler)
{
  pTask->State = TASK_EXITING;
  pTask->Replace = NewHandler;
}

void Task_Process(Task_t *pTask)
{
  // Common states
  switch (pTask->State)
  {
  case TASK_DELAY:
    if ((_CP0_GET_COUNT() - pTask->DelayStart) / CORE_US >= pTask->Delay)
      pTask->State = pTask->DelayNextState;
    break;
  case TASK_WAITMASK:
    if ((*pTask->WaitAddress & pTask->WaitMask) == pTask->WaitMask)
      pTask->State = pTask->WaitNextState;
    break;
  case TASK_WAITVAL:
    if (*pTask->WaitAddress == pTask->WaitMask)
      pTask->State = pTask->WaitNextState;
    break;
  }
}

void Task_SetDelay(Task_t *pTask, unsigned int DelayUs, unsigned int NextState)
{
  pTask->DelayNextState = NextState == TASK_AUTO ? pTask->State : NextState;
  pTask->State = TASK_DELAY;
  pTask->Delay = DelayUs;
  pTask->DelayStart = _CP0_GET_COUNT();
}

void Task_WaitMask(Task_t *pTask, unsigned int *pAddress, unsigned int Mask, unsigned int NextState)
{
  pTask->WaitNextState = NextState == TASK_AUTO ? pTask->State : NextState;
  pTask->State = TASK_WAITMASK;
  pTask->WaitAddress = pAddress;
  pTask->WaitMask = Mask;
}

void Task_WaitValue(Task_t *pTask, unsigned int *pAddress, unsigned int Value, unsigned int NextState)
{
  pTask->WaitNextState = NextState == TASK_AUTO ? pTask->State : NextState;
  pTask->State = TASK_WAITVAL;
  pTask->WaitAddress = pAddress;
  pTask->WaitMask = Value;
}
