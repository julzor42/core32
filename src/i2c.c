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
#include <core32/i2c.h>

void I2C_InitializeMaster(unsigned int Port, unsigned int Freq)
{
  // Disable and reset I2C
  I2CxCON(Port) = 0;
  
  PBDIV1_CYCLE_WAIT();
  
  I2CxBRG(Port) = ((PBCLK / 2 / Freq) - 2);
  
  I2C_Enable(Port);
}

void I2C_MasterWrite(unsigned int Port, unsigned char Data)
{   
    I2CxTRN(Port) = Data;
    while (I2CxSTAT(Port) & I2CXSTAT_TRSTAT);
} 

unsigned char I2C_MasterRead(unsigned int Port)
{   
    I2CxCONSET(Port) = I2CXCON_RCEN;
    while (!(I2CxSTAT(Port) & I2CXSTAT_RBF));
    return I2CxRCV(Port);
}

void I2C_Start(unsigned int Port)
{
    I2CxCONSET(Port) = I2CXCON_SEN;
    while (I2CxCON(Port) & I2CXCON_SEN);
}

void I2C_Stop(unsigned int Port)
{
    I2CxCONSET(Port) = I2CXCON_PEN;
    while (I2CxCON(Port) & I2CXCON_PEN);
}

void I2C_Ack(unsigned int Port)
{   
    I2CxCONCLR(Port) = I2CXCON_ACKDT;
    I2CxCONSET(Port) = I2CXCON_ACKEN;
    while (I2CxCON(Port) & I2CXCON_ACKEN);
}   

void I2C_NAck(unsigned int Port)
{   
    I2CxCONSET(Port) = I2CXCON_ACKDT;
    I2CxCONSET(Port) = I2CXCON_ACKEN;
    while (I2CxCON(Port) & I2CXCON_ACKEN);
}   

void I2C_Idle(unsigned int Port)
{
    unsigned int nCON   = I2CxCON(Port);
    unsigned int nSTAT  = I2CxSTAT(Port);
    while (nCON  & I2CXCON_SEN       || 
           nCON  & I2CXCON_PEN       || 
           nCON  & I2CXCON_RCEN      || 
           nCON  & I2CXCON_ACKEN     ||
           nSTAT & I2CXSTAT_TRSTAT
          );
}