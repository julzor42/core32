/*
  MIT License

  Copyright (c) 2024 Julien Delmotte

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
#ifndef _NT7603_H_
#define _NT7603_H_

#define LCD_SelectInstructionRegister() GPIO_ClearBit(LCDRS)
#define LCD_SelectDataRegister()        GPIO_SetBit(LCDRS)
#define LCD_SetWrite()                  GPIO_ClearBit(LCDRW)
#define LCD_SetRead()                   GPIO_SetBit(LCDRW)
#define LCD_Enable()                    GPIO_SetBit(LCDE)
#define LCD_Disable()                   GPIO_ClearBit(LCDE)
#define LCD_Write(data)                 GPIO_Write(PORT_LCD, data)
#define LCD_Read()                      GPIO_Read(PORT_LCD)

#define LCD_DELAY_STARTUP               30000
#define LCD_DELAY_CLEAR                 1640
#define LCD_DELAY_COMMAND               40

#define LCD_COMMAND_CLEAR               0x01
#define LCD_COMMAND_HOME                0x02
#define LCD_COMMAND_ENTRY_MODE_SET      0x04
#define LCD_COMMAND_DISPLAY             0x08
#define LCD_COMMAND_SHIFT               0x10
#define LCD_COMMAND_FUNCTION_SET        0x30
#define LCD_COMMAND_RAM_SET             0x40
#define LCD_COMMAND_DDRAM_SET           0x80

#define LCD_SHIFT_LEFT                  0
#define LCD_SHIFT_RIGHT                 1 << 2
#define LCD_SHIFT_CURSOR                0
#define LCD_SHIFT_DISPLAY               1 << 3

#define LCD_FUNCTION_DOTS_5X7           0
#define LCD_FUNCTION_DOTS_5X10          1 << 2
#define LCD_FUNCTION_LINE_1             0
#define LCD_FUNCTION_LINE_2             1 << 3

#define LCD_DISPLAY_BLINK               1 << 0
#define LCD_DISPLAY_CURSOR              1 << 1
#define LCD_DISPLAY_ON                  1 << 2
#define LCD_DISPLAY_OFF                 0

#define LCD_ENTRYMODE_SHIFT             1 << 0
#define LCD_ENTRYMODE_INCREMENT         1 << 1
#define LCD_ENTRYMODE_DECREMENT         0

#define LCD_Line2()   LCD_Goto(0x40)

void LCD_Init         ();
void LCD_Command      (unsigned char data);
void LCD_Clear        ();
void LCD_Home         ();
void LCD_Goto         (unsigned char dd);
void LCD_Shift        (unsigned char shift);
void LCD_FunctionSet  (unsigned char fs);
void LCD_Display      (unsigned char power);
void LCD_EntryModeSet (unsigned char mode);
void LCD_Print        (const char* s);
void LCD_Text         (const char* s);
void LCD_Format       (const char* format, ...);

#endif