#include <REGX51.H>
#ifndef	_LCD16x2_h_
#define _LCD16x2_h_

/*Cac lenh co ban cua LCD16x2
	0x00 	Bat LCD
	0x01	Xoa man hinh
	0x02	Di chuyen con tro ve dau man hinh
	0x06	Tu dong di chuyen con tro sang vi tri ke tiep khi xuat ra LCD mot ki tu 
	0x0C	Bat hien thi va tat con tro
	0x0E	Bat hien thi va bat con tro
	0xB0	Dua con tro ve vi tri dau dong 1
	0xC0	Dua con tro ve vi tri dau dong 2
	0x38	Giao tiep 8bit
	0x28	Giao tiep 4bit*/

#define LCD_RS  P1_0
#define LCD_RW  P1_1
#define LCD_EN  P1_2
#define LCD_D4  P0_4
#define LCD_D5  P0_5
#define LCD_D6  P0_6
#define LCD_D7  P0_7

void delay_us(unsigned int t);
void delay_ms(unsigned int t);
      
/***********Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void);
      

//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_Send4Bit(unsigned char Data);

// Ham Gui 1 Lenh Cho LCD
void LCD_SendCommand(unsigned char command);
      

void LCD_Clear();// Ham Xoa Man Hinh LCD
       

// Ham Khoi Tao LCD
void LCD_Init();
       

void LCD_Gotoxy(unsigned char , unsigned char );
        

void LCD_PutChar(unsigned char );
       

void LCD_Puts(char );
        


#endif