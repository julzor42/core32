#include <core32.h>

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
        Task_SleepMs(task, 1000);
      }
      break;
    }
}
