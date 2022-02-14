#include <core32.h>
#include <tcs3471/tcs3471.h>

void TCS3471_Initialize(unsigned int Port, unsigned int Freq)
{
    if (Freq == 0)
        Freq = 400000;
    
    I2C_InitializeMaster(Port, Freq);

    I2C_Idle(Port);
    
    // TODO
}