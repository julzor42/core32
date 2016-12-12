#include <core32.h>
#include <core32/extint.h>


void INT_SetExternalInterrupt(unsigned int Int, unsigned int Enabled, unsigned int Polarity, unsigned int Priority, unsigned int SubPriority)
{
  INT_EnableExternalInterrupt(Int, 0);
  INT_ClearExternalInterrupt(Int);
  switch (Int)
  {
    case INT_1:
    INTCONbits.INT1EP = Polarity;
    IPC1bits.INT1IP   = Priority;
    IPC1bits.INT1IS   = SubPriority;
    break;
  }
  INT_EnableExternalInterrupt(Int, Enabled);
}

void INT_EnableExternalInterrupt(unsigned int Int, unsigned int Enabled)
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
    case INT_1:
    IFS0bits.INT1IF = 0;
    break;
  }
}
