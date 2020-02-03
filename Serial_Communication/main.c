#include <REGX51.H>
#include <string.h>

#define off 	1
#define on	0
#define led1	P0_0
#define led2	P0_1
#define led3	P0_2
#define led4	P0_3
#define led5	P0_4
#define led6	P0_5
#define led7	P0_6
#define led8	P0_7

void send(unsigned char a){
	SBUF = a;
	while(TI==0);
	TI = 0;
}

void send_data(char *str){
	int i;
	int j = strlen(str);
	for(i=0;i<j;i++){
		send(str[i]);
	}
}

unsigned char receive(void){
	unsigned char c;
	while(RI==0);
	c = SBUF;
	RI = 0;
	return c;
}

void main(){
	unsigned char c;
	TMOD = 0x20;			// su dung timer 1 o che do 8 bit tu nap lai
	PCON = 0x80;			// smod =1 , x2 baudrate
	TH1 = 0xFA; 			// 4800 baud
	SCON = 0x50; 			// chon che do truyen 8 bit toc do timer 1, REN = 1 cho phep nhan du lieu
	TR1 = 1; 					
	
	while(1){
			
		c = receive();
		send(c);
		switch(c){
			case '1':	led1 = ~led1; break;
			case '2':	led2 = ~led2; break;
			case '3':	led3 = ~led3; break;
			case '4':	led4 = ~led4; break;
			case '5':	led5 = ~led5; break;
			case '6':	led6 = ~led6; break;
			case '7':	led7 = ~led7; break;
			case '8':	led8 = ~led8; break;
			default: led1=led3=led5=led7 = ~led1; led2=led4=led6=led8=~led1; break;
				
			}
	}
}