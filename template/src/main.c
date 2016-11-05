#include <core32.h>

//
// Configuration bits
//
#pragma config POSCMOD 	= XT
#pragma config FNOSC   	= PRIPLL
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL  = MUL_20
#pragma config FPLLODIV = DIV_1
#pragma config FPBDIV   = 2

void Program(Task_t* task)
{
    Task_Switch(task)
    {
      case TASK_START:
      {
        ADC_SetDigital(PINS_ALL);
        GPIO_SetOutput(PortA, PINS_ALL);
      }
      break;
      
      case TASK_IDLE:
      {
        GPIO_ToggleBits(PortA, PINS_ALL);
        Task_Sleep(task, 1000000);
      }
      break;
    }
}
