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
#include <core32/tasks/console.h>

#ifdef USE_TASK_CONSOLE
#include <string.h>

void Task_Console(Task_t* task);

void Console_Attach(uint32_t Port, CONSOLE_HANDLER Handler, Console_t* pConsole)
{
    memset(pConsole, 0, sizeof(Console_t));
    pConsole->Port      = Port;
    pConsole->Handler   = Handler;
    pConsole->Flags     = 0;

    Task_Create(Task_Console, pConsole);
}

static void PushCharacter(Console_t* pConsole, char c)
{
    if (pConsole->Echo)
        UART_PutChar(pConsole->Port, c);
    pConsole->Command[pConsole->Length++] = c;
}

void Task_Console(Task_t* task)
{
    char c;
    Console_t* pConsole;
    
    pConsole = (Console_t*)task->Data;//Task_GetData(task, Console_t*);

    Task_Switch(task)
    {
        case TASK_START:
        break;

        case TASK_IDLE:
        {
            while (UART_HasData(pConsole->Port))
            {
                c = UxRXREG(pConsole->Port);
                if (c == 13) // Enter
                {
                    if (pConsole->Echo) UART_PutChar(pConsole->Port, c);
                    pConsole->Command[pConsole->Length] = 0;
                    pConsole->Handler(pConsole->Command, pConsole->Length);
                    pConsole->Length = 0;
                }
                if (c == 8) // Backspace
                {
                    if (pConsole->Length > 0) pConsole->Length--;
                    if (pConsole->Echo) UART_PutChar(pConsole->Port, c);
                }
                else
                {
                    if (pConsole->Length < CONSOLE_COMMAND_MAXLEN)
                        PushCharacter(pConsole, c);
                }
            }
            // TODO: allow sleep, wait for UART interrupt
        }
        break;
    }
}

#endif
