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
#ifndef _I2C_H_
#define _I2C_H_

#define BASEADDRESS_I2C     0xBF805000
#define I2CxCON_BASE(x)     _SFR_ADDR(BASEADDRESS_I2C, 0x100, x)

//
// SFRs
//
#define I2CxCON(x)          _SFR(I2CxCON_BASE(x))
#define I2CxCONCLR(x)       _SFR_CLR(I2CxCON_BASE(x))
#define I2CxCONSET(x)       _SFR_SET(I2CxCON_BASE(x))
#define I2CxSTAT(x)         _SFR(I2CxCON_BASE(x)     + 0x10)
#define I2CxSTAT_CLR(x)     _SFR_CLR(I2CxCON_BASE(x) + 0x10)
#define I2CxSTAT_SET(x)     _SFR_SET(I2CxCON_BASE(x) + 0x10)
#define I2CxADD(x)          _SFR(I2CxCON_BASE(x)     + 0x20)
#define I2CxMSK(x)          _SFR(I2CxCON_BASE(x)     + 0x30)
#define I2CxBRG(x)          _SFR(I2CxCON_BASE(x)     + 0x40)
#define I2CxTRN(x)          _SFR(I2CxCON_BASE(x)     + 0x50)
#define I2CxRCV(x)          _SFR(I2CxCON_BASE(x)     + 0x60)

//
// I2CxCON
//
#define I2CXCON_SEN         1 << 0
#define I2CXCON_RSEN        1 << 1
#define I2CXCON_PEN         1 << 2
#define I2CXCON_RCEN        1 << 3
#define I2CXCON_ACKEN       1 << 4
#define I2CXCON_ACKDT       1 << 5
#define I2CXCON_STREN       1 << 6
#define I2CXCON_GCEN        1 << 7
#define I2CXCON_SMEN        1 << 8
#define I2CXCON_DISSLW      1 << 9
#define I2CXCON_A10M        1 << 10
#define I2CXCON_STRICT      1 << 11
#define I2CXCON_SCLREL      1 << 12
#define I2CXCON_SIDL        1 << 13
#define I2CXCON_ON          1 << 15

//
// I2CxSTAT
//
#define I2CXSTAT_TBF        1 << 0
#define I2CXSTAT_RBF        1 << 1
#define I2CXSTAT_RW         1 << 2
#define I2CXSTAT_S          1 << 3
#define I2CXSTAT_P          1 << 4
#define I2CXSTAT_DA         1 << 5
#define I2CXSTAT_I2COV      1 << 6
#define I2CXSTAT_IWCOL      1 << 7
#define I2CXSTAT_ADD10      1 << 8
#define I2CXSTAT_GCSTAT     1 << 9
#define I2CXSTAT_BCL        1 << 10
#define I2CXSTAT_TRSTAT     1 << 14
#define I2CXSTAT_ACKSTAT    1 << 15

//
// I2C ports
//
#define I2C_3               0
#define I2C_4               1
#define I2C_5               2
#define I2C_1               3
#define I2C_2               4

//
// Macros
//
#define       I2C_Enable(port)        I2CxCONSET(port) = I2CXCON_ON
#define       I2C_Disable(port)       I2CxCONCLR(port) = I2CXCON_ON
#define       I2C_IsEnabled(port)     (I2CxCON & I2CXCON_ON)

//
// Functions
//
void          I2C_InitializeMaster    (unsigned int Port, unsigned int Freq);
void          I2C_MasterWrite         (unsigned int Port, unsigned char Data);
unsigned char I2C_MasterRead          (unsigned int Port);
void          I2C_Start               (unsigned int Port);
void          I2C_Stop                (unsigned int Port);
void          I2C_Ack                 (unsigned int Port);
void          I2C_NAck                (unsigned int Port);
void          I2C_Idle                (unsigned int Port);

#endif /* _UART_H_ */
