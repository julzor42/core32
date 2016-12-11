#include "console.h"

#ifdef USE_TASK_CONSOLE
#include <string.h>

void Task_Console(Task_t* task);

void Console_Attach(uint32_t Port, CONSOLE_HANDLER Handler, Console_t* pConsole)
{
    memset(pConsole, 0, sizeof(Console_t));
    pConsole->Port      = Port;
    pConsole->Handler   = Handler;

    Task_Create(Task_Console, pConsole);
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
                if (c == 13)
                {
                    pConsole->Command[pConsole->Length] = 0;
                    pConsole->Handler(pConsole->Command, pConsole->Length);
                    pConsole->Length = 0;
                }
                else
                {
                    if (pConsole->Length < CONSOLE_COMMAND_MAXLEN)
                        pConsole->Command[pConsole->Length++] = c;
                }
            }
            // TODO: allow sleep, wait for UART interrupt
        }
        break;
    }
}

#endif
