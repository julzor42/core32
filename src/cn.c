#include <core32.h>
#include <core32/cn.h>

void CN_SetInterrupt(unsigned int Enabled, unsigned int Priority, unsigned int SubPriority)
{
  CN_EnableInterrupt(DISABLED);
  CN_SetPriority(Priority);
  CN_SetSubPriority(SubPriority);
  CN_ClearInterrupt();
  CN_EnableInterrupt(Enabled);
}

