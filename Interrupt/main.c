#include <REGX51.H>

#define led1	P2_0
#define	led2	P2_1
#define led3	P2_2
#define led4	P2_3
#define led5	P2_4
#define led6	P2_5
#define on	1
#define off 0
unsigned int i, a ,b ,t;
unsigned int f, count;
char so[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x82, 0xf8, 0x80, 0x90};
unsigned char tn, cn, n, tram, chuc, dv;
void delay(unsigned int x){
	while(x--);
}

void delay_ms(int ms){
	while(ms--){
	TMOD = 0x11; 	// dung timer 1 o che do dem 16bit 
	TH1 = 0xfc; 	// nap gia tri dem 1ms
	TL1 = 0x18; 
	TR1 = 1;			// khoi dong timer
	while(!TF1);
	TF1 = 0;
	TR1 = 0;
	}
}

void Interrupt_Init(void){
	TMOD = 0x11;
	TH0 = 0xfc;
	TL0 = 0x31;
	TR0 = 1;		
	EX0 = 1;			
	ET0 = 1;
	//EX1 = 1;
	EA = 1;
	P3_2 = 1; 		// cau hinh che do input
	IT0 = 1;			// ngat SUON XUONG
	//IT1 = 1;			// ngat suon xuong
}

void Display_Freg(void){	//ham hien thi gia tri tan so do dc
	
	
		for(i = 0; i<= 16; i++){
			led1 = on; P0 = so[tn]; 		delay_ms(10);	led1 = off;
			led2 = on; P0 = so[cn]; 		delay_ms(10);	led2 = off;
			led3 = on; P0 = so[n]; 			delay_ms(10);	led3 = off;
			led4 = on; P0 = so[tram];		delay_ms(10);	led4 = off;
			led5 = on; P0 = so[chuc]; 	delay_ms(10);	led5 = off;
			led6 = on; P0 = so[dv]; 		delay_ms(10);	led6 = off;
		}
}

void tachso(unsigned int freg){			//tach gia tri tan so
	tn = freg/100000;
	cn = (freg%100000)/10000;
	n = (freg%10000)/1000;
	tram = (freg%1000)/100;
	chuc = (freg%100)/10;
	dv = freg%10;
}

void main(){
//	TMOD = 0x01; 	// dung timer 1 o che do dem 16bit 
//	TH0 = 0xfc; 	// nap gia tri dem 1ms
//	TL0 = 0x18; 
//	TR0 = 1;			// khoi dong timer
//	EA = 1; 			// cho phep ngat all
//	ET0 = 1; 			// ngat timer 0 voi co ngat la TF0
//	EX0 = 1;			// ngat ngoai 0 co ngat IE0 
//	EX1 = 1;			// ngat ngoai 1 co ngat IE1	 
//	P1 = 0x00;
//	led1 = led2 =0;
		Interrupt_Init();
	while(1){
		Display_Freg();
		
	}
}

//Khai bao ham ngat theo syntax void name(void) interruptX // X: stt ngat 

void ISR_EX0_Handler(void)	interrupt 0{	//ham xu li ngat ngoai 0
	count++;
//	int a = 50000;
//	led1 = led2 = 0;
//	P1_0 = 1; 
//	while(a--);
//	P1_0 = 0;
	
}

void ISR_ET0_Handler(void)	interrupt 1{	//ham xu li ngat Timer 0
	TH0 = 0xfc; 	// nap gia tri dem 1ms
	TL0 = 0x31; 
	t++;
	TR0 = 1;			//khoi dong lai timer0 
	if(t == 1000){
		f = count;
		tachso(f);
		count = 0;
		t = 0;
	}
}

//void ISR_EX1_Handler(void) interrupt 2{		//ham xu li ngat ngoai 1
//	led1 = led2 = 1;
//	for(i = 0;i<5;i++){
//		P1_1 = 1;
//	  a = 25000;
//		while(a--);
//		P1_1 = 0;
//	  b = 25000;
//		while(b--);
//	}
//}
		
		
