#include <core32.h>
#include <nunchuck/nunchuck.h>

void Nunchuk_Initialize(unsigned int Port, unsigned int Freq)
{
    if (Freq == 0)
        Freq = 400000;
    
    I2C_InitializeMaster(Port, Freq);

    I2C_Idle(Port);

    // Nunchuk handshake
    I2C_Start(Port);
    I2C_Idle(Port);
    I2C_MasterWrite(Port, 0xA4);
    I2C_MasterWrite(Port, 0xF0);
    I2C_MasterWrite(Port, 0x55);
    I2C_Stop(Port);

    I2C_Start(Port);
    I2C_Idle(Port);
    I2C_MasterWrite(Port, 0xA4);
    I2C_MasterWrite(Port, 0xFB);
    I2C_MasterWrite(Port, 0x00);
    I2C_Stop(Port);
}

void Nunchuk_Read(unsigned int Port, unsigned char* pOutput)
{
    I2C_Start(Port);
    I2C_Idle(Port);
    I2C_MasterWrite(Port, 0xA4);
    I2C_MasterWrite(Port, 0x00);
    I2C_Stop(Port);

    // Request reading
    I2C_Start(Port);
    I2C_Idle(Port);
    I2C_MasterWrite(Port, 0xA5);
    I2C_Idle(Port);

    // Bytes reception
    unsigned int nByte;
    for (nByte = 0; nByte < 5; nByte++)
    {
        pOutput[nByte] = I2C_MasterRead(Port);
        I2C_Ack(Port);
        I2C_Idle(Port); 
    }
    pOutput[5] = I2C_MasterRead(Port);       // Last byte to be read
    I2C_NAck(Port);
    I2C_Idle(Port);
    I2C_Stop(Port);
}
