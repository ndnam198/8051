#ifndef _LCD16x2_H_
#define _LCD16x2_H_

#define _LCD_CLEAR				1   		
#define _LCD_RETURN_HOME		2
#define _LCD_ENTRY_MODE			6
#define _LCD_TURN_OFF			8
#define _LCD_TURN_ON			12
#define _LCD_CURSOR_OFF			12 	  
#define _LCD_UNDERLINE_ON		14
#define _LCD_BLINK_CURSOR_ON	15
#define _LCD_MOVE_CURSOR_LEFT	16
#define _LCD_MOVE_CURSOR_RIGHT	17
#define _LCD_SHIFT_LEFT			24
#define _LCD_SHIFT_RIGHT		28
#define _LCD_4BIT_1LINE_5x7FONT	0x20
#define _LCD_4BIT_2LINE_5x7FONT	0x28
#define _LCD_8BIT_1LINE_5x7FONT	0x30
#define _LCD_8BIT_2LINE_5x7FONT	0x38
#define _LCD_FIRST_ROW			128
#define _LCD_SECOND_ROW			192

void Lcd_Init(void);

void Lcd_Cmd(unsigned char cmd);

void Lcd_Chr_Cp(unsigned char achar);
	
void Lcd_Chr(unsigned char row, unsigned char columnm,unsigned char achar);

void Lcd_Out_Cp(unsigned char * str);

void Lcd_Out(unsigned char row, unsigned char column,unsigned char * str);

void Lcd_Custom_Chr(unsigned char location, unsigned char * lcd_char);

void Lcd_Write_High_Nibble(unsigned char);
void Lcd_Write_Low_Nibble(unsigned char );
void Lcd_Delay_us(unsigned char);
void Lcd_Clear();

#endif