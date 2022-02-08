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
#include <p32xxxx.h>
#include <core32conf.h>
#include <il9341/il9341.h>

unsigned char TFT_BackBuffer[320*240];

void TFT_RawShort    (unsigned short data)   { PMDIN = data >> 8; Nop(); Nop(); PMDIN = data; Nop(); Nop(); }
void TFT_RawByte     (unsigned char byte)    { PMDIN = byte; Nop(); Nop(); }
void TFT_RawShortRev (unsigned short data)   { PMDIN = data; Nop(); PMDIN = data >> 8; }
void TFT_SendCommand (unsigned int index)    { TFT_Begin(); TFT_RS = 0; TFT_RawByte(index); TFT_End(); TFT_RS = 1; }

void TFT_SetAddress(unsigned short x, unsigned short y)
{
    TFT_SendCommand(0x2a);
    TFT_Begin();
    TFT_RawShort(x);
    TFT_RawByte(0x01);
    TFT_RawByte(0xdf);
    TFT_End();
    
    TFT_SendCommand(0x2b); 
    TFT_Begin();
    TFT_RawShort(y);
    TFT_RawByte(0x01);
    TFT_RawByte(0x3f);
    TFT_End();
    
    TFT_SendCommand(0x2c);
}
 
void TFT_WriteReg1(unsigned char index, unsigned char value)
{
    TFT_SendCommand(index);
    
    TFT_Begin();
    TFT_RawByte(value);
    TFT_End();
}

void TFT_WriteReg2(unsigned char index, unsigned char value1, unsigned char value2)
{
    TFT_SendCommand(index);
    
    TFT_Begin();
    TFT_RawByte(value1);
    TFT_RawByte(value2);
    TFT_End();
}

void TFT_WriteReg3(unsigned char index, unsigned char value1, unsigned char value2, unsigned char value3)
{
    TFT_SendCommand(index);
    
    TFT_Begin();
    TFT_RawByte(value1);
    TFT_RawByte(value2);
    TFT_RawByte(value3);
    TFT_End();
}


void TFT_DelayMs(unsigned int SysFreq, unsigned int time)
{
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < (SysFreq / 2000) * time);
}

void TFT_Initialize()
{
    TFT_RD_TRIS         = 0;
    TFT_WR_TRIS         = 0;
    TFT_RS_TRIS         = 0;
    TFT_CS_TRIS         = 0;
    TFT_RST_TRIS        = 0;

    TFT_RD              = 1;
    TFT_WR              = 1;
    
    // PMP setup
    PMCON               = 0;
    PMMODEbits.MODE     = 2;  // Master 2
    PMMODEbits.MODE16   = 0;  // 16 bit mode
    PMCONbits.PTRDEN    = 1;
    PMCONbits.PTWREN    = 1;
    PMCONbits.PMPEN     = 1;
    
    // Reset phase
    TFT_RST = 1; TFT_DelayMs(SYSTEM_FREQ, 100);
    TFT_RST = 0; TFT_DelayMs(SYSTEM_FREQ, 100);
    TFT_RST = 1; TFT_DelayMs(SYSTEM_FREQ, 100);

    TFT_WriteReg1(0x36, 0x69);	// Memory access control
    TFT_WriteReg1(0x3A, 0x05);  // Pixel Format (16 BPP)
    
    TFT_SendCommand(0x21);                  // Display inversion
    TFT_WriteReg3(0xB6, 0x00, 0x20, 0x27);  // Display Function Control (Orientation)
    
    // Get out of sleep
    TFT_SendCommand(0x11);
    TFT_DelayMs(SYSTEM_FREQ, 100);
    
    // Display ON
    TFT_SendCommand(0x29);
}

void TFT_Flip()
{
    unsigned char* pData;
    unsigned char* pEnd;
        
    TFT_SetAddress(0, 0);

    TFT_Begin();
    
    pData = (unsigned char*)&TFT_BackBuffer;
    pEnd  = pData + TFT_PIXELS;
    
    while (pData < pEnd)
    {
        unsigned int color = *pData++ * 255;
        TFT_RawShortRev(color);
    }
    
    TFT_End();
}

void TFT_Clear(unsigned char Color)
{
    unsigned int* pData;
    unsigned int* pEnd;
    unsigned int  Color4;
 
    pData = (unsigned int*)&TFT_BackBuffer;
    pEnd  = pData + TFT_PIXELS / 4;
    
    Color4 = Color | Color << 8 | Color << 16 | Color << 24;
    
    while (pData < pEnd)
    {
        *pData++ = Color4;
    }
}

