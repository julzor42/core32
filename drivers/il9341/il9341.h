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
#ifndef _ILI9341_H_
#define _ILI9341_H_

#define TFT_WIDTH       320
#define TFT_HEIGHT      240
#define TFT_PIXELS      TFT_WIDTH * TFT_HEIGHT

extern unsigned char    TFT_BackBuffer[];

void                    TFT_Initialize  (unsigned int SysFreq);
void                    TFT_Clear       (unsigned char Color);
void                    TFT_Flip        ();

#define TFT_Plot(x, y, Color)           TFT_BackBuffer[x + y * TFT_WIDTH] = Color

#define TFT_RD          _LATD5
#define TFT_WR          _LATD4
#define TFT_RS          _LATD9
#define TFT_CS          _LATD10
#define TFT_RST         _LATD7

#define TFT_RD_TRIS     _TRISD5
#define TFT_WR_TRIS     _TRISD4
#define TFT_RS_TRIS     _TRISD9
#define TFT_CS_TRIS     _TRISD10
#define TFT_RST_TRIS    _TRISD7

#endif /* _ILI9341_H_ */
