#include <REGX51.H>

void delay_ms(){
	TMOD = 0x01;			 // timer 0, che do 1
	TH0 = 0x03;
	TL0 = 0x99;
	TR0 = 1;	
	while(!TF0);				//neu TF0 = 1 tuc tran bo dem can lap lai
	TF0 = 0;	
	TR0 = 0;						// dung timer 0 
}

void main(){
	P3_0 = 0;
	while(1){
		P3_0 = ~P3_0;
		delay_ms();
	}
}