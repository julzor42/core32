#include <core32.h>
#ifdef USE_TASK_CONSOLE

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

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

#endif /* _CONSOLE_H_ */

#endif