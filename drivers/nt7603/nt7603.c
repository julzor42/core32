#include <core32.h>
#include <stdio.h>
#include <stdarg.h>
#include <nt7603/nt7603.h>

void LCD_Command(unsigned char data)
{
  LCD_Write(data);
  LCD_Enable();
  System_DelayUs(LCD_DELAY_COMMAND);
  LCD_Disable();
}

void LCD_Clear()
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_CLEAR);
  System_DelayUs(LCD_DELAY_CLEAR);
  LCD_SelectDataRegister();
}

void LCD_Home()
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_HOME);
  System_DelayUs(LCD_DELAY_CLEAR);
  LCD_SelectDataRegister();
}

void LCD_Goto(unsigned char dd)
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_DDRAM_SET | dd);
  LCD_SelectDataRegister();
}

void LCD_Shift(unsigned char shift)
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_SHIFT);
  LCD_SelectDataRegister();
}

void LCD_FunctionSet(unsigned char fs)
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_FUNCTION_SET | fs);
  LCD_SelectDataRegister();
}

void LCD_Display(unsigned char power)
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_DISPLAY | power);
  LCD_SelectDataRegister();
}

void LCD_EntryModeSet(unsigned char mode)
{
  LCD_SelectInstructionRegister();
  LCD_Command(LCD_COMMAND_ENTRY_MODE_SET | mode);
  LCD_SelectDataRegister();
}

void LCD_Init()
{
  GPIO_SetOutput(PORT_LCD, PINS_L);
  GPIO_SetBitOutput(LCDE);
  GPIO_SetBitOutput(LCDRW);
  GPIO_SetBitOutput(LCDRS);

  LCD_Disable();
  LCD_SetWrite();

  System_DelayUs(LCD_DELAY_STARTUP);

  LCD_FunctionSet(LCD_FUNCTION_DOTS_5X10 | LCD_FUNCTION_LINE_2);
  LCD_Display(LCD_DISPLAY_ON | LCD_DISPLAY_BLINK);  
  
  LCD_Clear();
  LCD_EntryModeSet(LCD_ENTRYMODE_INCREMENT);
}

void LCD_Print(const char* s)
{
  while (*s)
  {
    LCD_Command(*s++);
  }
}

void LCD_Text(const char* s)
{
  LCD_Clear();
  while (*s)
  {
    if (*s == '\n')
    {
      LCD_Line2();
    }
    else 
    {
      LCD_Command(*s);
    }
    s++;
  }
}

void LCD_Format(const char* format, ...)
{
  char buffer[32] = {0};
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  LCD_Text(buffer);
}
