#include "lcd16x2.h"
#include "port.h"
#include <REGX51.H>
#include "delay.h"
#icnlude "string.h"

void Lcd_Write_High_Nibble(unsigned char b)
{
	LCD_D7 = b & 0x80;
	LCD_D6 = b & 0x40;
	LCD_D5 = b & 0x20;
	LCD_D4 = b & 0x10; 	
}

void Lcd_Write_Low_Nibble(unsigned char b)
{
 	LCD_D7 = b & 0x08;
	LCD_D6 = b & 0x04;
	LCD_D5 = b & 0x02;
	LCD_D4 = b & 0x01;
}

/*-------------------------------------*-
	Lcd_Delay_us - Local Function
-*-------------------------------------*/
void Lcd_Delay_us(unsigned char t)
{
 	while(t--);
}

void Lcd_Init()
{	
	LCD_RS = 0;
	LCD_EN = 0;

	LCD_RW = 0;

	Delay_ms(20);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;
    Delay_ms(5);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;
    Lcd_Delay_us(100);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;


	Lcd_Write_Low_Nibble(0x02);
	LCD_EN = 1;
	LCD_EN = 0;
	Delay_ms(1);
		
	Lcd_Cmd(_LCD_4BIT_2LINE_5x7FONT);
	Lcd_Cmd(_LCD_TURN_ON);
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Cmd(_LCD_ENTRY_MODE);
}

/*-------------------------------------*-
	Lcd_Cmd
	- Gui lenh cho LCD
-*-------------------------------------*/
void Lcd_Cmd(unsigned char cmd)
{

	LCD_RS = 0;
	Lcd_Write_High_Nibble(cmd); 
	LCD_EN = 1;
	LCD_EN = 0;

	Lcd_Write_Low_Nibble(cmd);
	LCD_EN = 1;
	LCD_EN = 0;

	switch(cmd)
	{
		case _LCD_CLEAR:
		case _LCD_RETURN_HOME:
			Delay_ms(2);
			break;
		default:
			Lcd_Delay_us(37);
			break;
	}
}

/*-------------------------------------*-
	Lcd_Chr
	- In ky tu ra man hinh tai (row, column)
-*-------------------------------------*/
void Lcd_Chr(unsigned char row, unsigned char column, 
	unsigned char out_char)
{
	unsigned char add;
	add = (row==1?0x80:0xC0);
	add += (column - 1);
	Lcd_Cmd(add);
	Lcd_Chr_Cp(out_char);
}

/*-------------------------------------*-
	Lcd_Out
	- In chuoi (text) ra man hinh
	- Vi tri bat dau tai (row, column)
-*-------------------------------------*/
void Lcd_Out(unsigned char row, unsigned char column, 
	unsigned char* text)
{
	unsigned char add;
	add = (row==1?0x80:0xC0);
	add += (column - 1);
	Lcd_Cmd(add);
	Lcd_Out_Cp(text); 
}

void Lcd_Clear(){
	Lcd_Cmd(_LCD_CLEAR);
}
