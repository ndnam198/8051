#include <REGX52.H>
#include <stdio.h>
#define LCD_RS  P0_0
#define LCD_RW  P0_1
#define LCD_EN  P0_2
#define LCD_D4  P0_4
#define LCD_D5  P0_5
#define LCD_D6  P0_6
#define LCD_D7  P0_7
//====================================//
#define bt_up	    P1_0	
#define bt_dow	    P1_1
#define bt_right	P1_2
#define bt_left	    P1_3
#define stop	    P1_4
#define start	    P1_5
#define low			P3_6
#define high		P3_7		
 //=================oOo=============//
unsigned int count=0,y,z[4],g,chieu;
unsigned char ud;
float dem,x;

char duty ;
//=================oOo=============//
void delay_us(unsigned int t){
        unsigned int i;
        for(i=0;i<t;i++);
}
void delay_ms(unsigned int t){
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);}
/***********Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void){
        LCD_EN =1;
        delay_us(3);
        LCD_EN =0;
        delay_us(90); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_Send4Bit(unsigned char Data){
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

void num_dsp( float number)
{
    unsigned char str[5];
	sprintf(str,"%3.0f",number);
	LCD_Puts(str);
}
//====================PWM================================
sbit PWM_PIN = P3^0;

unsigned int T, Ton, Toff;

unsigned char Ton_h_reload, Ton_l_reload, Toff_h_reload, Toff_l_reload;

// ck (us)
void PWM_Init(unsigned int ck)			//ck = 0x0000 - 0xffff TIMER 16BIT
{	
	PWM_PIN = 1;
	TMOD |= 0x01;		// Timer0 hoat dong o mode 1
	ET0 = 1;			// Cho phep ngat Timer0
	EA = 1;				// Cho phep ngat toan cuc	
	T  = ck;
	Ton = T/2;			// Duty Cycle = 50%
	Toff = T - Ton;

	Ton_h_reload = (65536-Ton)>>8;		 //tinh toan gia tri Ton
	Ton_l_reload = (65536-Ton)&0x00FF;

	Toff_h_reload = (65536-Toff)>>8;	//tinh toan gia tri Toff
	Toff_l_reload = (65536-Toff)&0x00FF;
	
	TH0 = Ton_h_reload;					// nap gia tri Ton cho T0
	TL0 = Ton_l_reload;	
}

void PWM_Start()
{
	TR0 = 1;			// Timer0 bat dau dem
}

void PWM_Stop()
{
 	TR0 = 0;			// Timer0 ngung dem
}

// duty: 0 den 100
void PWM_Set_Duty()	   // chuong trinh con thay doi do rong xung
{	
	
	
	if(duty == 0)
	{
		PWM_PIN = 0;
		ET0 = 0;
	}
	else if(duty == 100)
	{
		PWM_PIN = 1;
		ET0 = 0;
	}
	else
	{
		Ton = ((unsigned long)T)*duty/100;
		Toff = T - Ton;
	
	   	Ton_h_reload = (65536-Ton)>>8;
		Ton_l_reload = (65536-Ton)&0x00FF;
	
		Toff_h_reload = (65536-Toff)>>8;
		Toff_l_reload = (65536-Toff)&0x00FF;

		ET0 = 1;
	}
	
}

//=======================================================
void chieu_quay() //chuong trinh con xac dinh chieu quay

{	
       if(bt_right==0) {P2=0x03;}
	   if(bt_left==0)  {P2=0x0C;}
	   if(x==0)
		  {
	       if(P2==0x03)  {LCD_Gotoxy(0,0);LCD_Puts("P"); }
		   if(P2==0x0C)  {LCD_Gotoxy(0,0); LCD_Puts("T");}
		  }
	if(stop==0)
	P2=0x00;
		
}  
void canhbao()			  // chuong trinh con canh bao 
{
    if(x>1800) high=1;
	if(x<500)  low=1;
	if(x<=1800&&x>=500) low=high=0; 
 
	 
}
void cd()				  // chuong trinh con tinh toan va hien thi
{
    x=(60*dem)/(360*0.01980);
	
	LCD_Gotoxy(8,0);
	LCD_Puts("%PWM:");
	num_dsp(ud);
	LCD_Gotoxy(0,1);
	LCD_Puts("Toc do:");
   
	num_dsp(x);
	LCD_Puts(" v/p");

}
void set_ud()   // chuong trinh con tang giam duty bang nut nhan
{
    if(bt_up==0) ud=ud+1; 
	if(bt_dow==0) ud=ud-1;
	if(ud>100) ud=100;
	if (start==0) duty=ud;
}
void main()
{		LCD_Init();
	EA=0;
	TMOD|=0x50;		  
	TH1=0x00;
	TL1=0x00;
    //	khoi tao T2
    T2CON=0x00;
	RCAP2H=0xB1;RCAP2L=0xE0;
	
	TR2=1;
	ET2=1;
    EA=1;
	//khoi tao cong vao ra
	P2=0x00;
	low=high=0;
	LCD_Clear();
//------------------
	duty=ud=45;
    PWM_Init(10000); //t=10ms

        while(1)
		{
	//-----------------------------
	chieu_quay();
	cd();
	canhbao();
	//---------------
	PWM_Set_Duty();
	PWM_Start();	
		}
}

void INT_T2() interrupt 5 using 0		   //chuong trinh ngat lay mau xung, ngat timer 2
{	unsigned char high,low;

  	TF2=0;
	TR1=0;
	high=TH1; low=TL1;
	y=high ;y<<=8; y|=low;
	TL1=TH1=0x00;
	TR1=1;
	
	z[count]=y;
	count++; 
	if(count==3){dem=((z[0]+z[1]+z[2])/3); count=0;}
	//------------------
	set_ud();
		
				   											                                                                  												 
}
//=============================================================
void INT_T0() interrupt  1				  // chuong trinh ngat bam xung PWM, ngat timer 0
{
	
	PWM_PIN = !PWM_PIN;
	if(PWM_PIN==0)
	{
	 	TH0 = Toff_h_reload;
		TL0 = Toff_l_reload;
	}
	else
	{
	 	TH0 = Ton_h_reload;
		TL0 = Ton_l_reload;
	}
}
