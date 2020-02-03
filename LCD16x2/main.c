#include <REGX51.H>
#include "LCD16x2.h"
 
#define LCD_RS  P1_0
#define LCD_RW  P1_1
#define LCD_EN  P1_2
#define LCD_D4  P0_4
#define LCD_D5  P0_5
#define LCD_D6  P0_6
#define LCD_D7  P0_7

void delay_us(unsigned int t){
        unsigned int i;
        for(i=0;i<t;i++);
}
void delay_ms(unsigned int t){
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);}
/***********Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void){			//tao mot xung suon xuong o EN de bao hieu 
        LCD_EN =1;
        delay_us(3);
        LCD_EN =0;
        delay_us(50); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_Send4Bit(unsigned char Data){			// gui 4 bit 
        LCD_D4=Data & 0x01;
        LCD_D5=(Data>>1)&1;
        LCD_D6=(Data>>2)&1;
        LCD_D7=(Data>>3)&1;
}
// Ham Gui 1 Lenh Cho LCD
void LCD_SendCommand(unsigned char command){
        LCD_Send4Bit(command >>4);/* Gui 4 bit cao */
        LCD_Enable();
        LCD_Send4Bit(command); /* Gui 4 bit thap*/
        LCD_Enable();
}
void LCD_Clear(){// Ham Xoa Man Hinh LCD
        LCD_SendCommand(0x01); 
        delay_us(10);
}
// Ham Khoi Tao LCD
void LCD_Init(){
        LCD_Send4Bit(0x00);	  //turn on LCD
        delay_ms(20);
        LCD_RS=0;
        LCD_RW=0;
        LCD_Send4Bit(0x03);	  //function setting
        LCD_Enable();
        delay_ms(5);
        LCD_Enable();
        delay_us(100);
        LCD_Enable();
        LCD_Send4Bit(0x02);	  //di chuyen con tro ve dau man hnh
        LCD_Enable();
        LCD_SendCommand( 0x28 ); //lua chon che do 4 bit
        LCD_SendCommand( 0x0c);  // bat hien thi va tat con tro di
        LCD_SendCommand( 0x06 );
        LCD_SendCommand(0x01);
}
void LCD_Gotoxy(unsigned char x, unsigned char y){
        unsigned char address;
        if(!y)address=(0x80+x);
        else address=(0xc0+x);
        delay_us(1000);
        LCD_SendCommand(address);
        delay_us(50);
}
void LCD_PutChar(unsigned char Data){
        LCD_RS=1;
        LCD_SendCommand(Data);
        LCD_RS=0 ;
}
void LCD_Puts(char *s){
        while (*s){
                LCD_PutChar(*s);
                s++;
        }
}

void main(){
		LCD_Init();
		LCD_Gotoxy(0,0);
		LCD_Puts("hello world");
		delay_ms(3000);
		LCD_Clear();
		while(1){
			LCD_Puts("LCD 16x2 project");
			delay_ms(1000);
			LCD_Clear();
			delay_ms(500);
		}
}