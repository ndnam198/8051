#include <REGX51.H>


#define hour 		P3_5
#define min 		P3_6
#define second  P3_7

#define led_gio1			P2_0
#define led_gio2			P2_1
#define led_phut1		P2_2
#define led_phut2		P2_3
#define led_giay1		P2_4
#define led_giay2		P2_5

#define on	0
#define off	1

char so[] = {0xBF, 0x86, 0xDB, 0XCF, 0XE6, 0XED, 0XFD, 0X87, 0XFF, 0XEF};

void delay_ms(int ms){
	while(ms--){
		TMOD = 0x01;
		TH0 = 0xfc;
		TL0 = 0x18;
		TR0 = 1;
		while(!TF0);
		TF0 = 0;
		TR0 = 0;
	}
}

void hienThi(unsigned char gio, unsigned char phut, unsigned char giay){
		unsigned char chuc_gio, dv_gio, chuc_phut, dv_phut, chuc_giay, dv_giay, i;
		chuc_gio = gio/10; dv_gio = gio%10;
		chuc_phut = phut/10; dv_phut = phut%10;
		chuc_giay = giay/10; dv_giay = giay%10;
		for(i=0;i<30;i++){
			led_gio1 = on; 	P0 = so[chuc_gio]; 	delay_ms(5); 		led_gio1 = off; 
			led_gio2 = on; 	P0 = so[dv_gio]; 		delay_ms(5); 		led_gio2 = off; 
			led_phut1 = on; P0 = so[chuc_phut]; delay_ms(5);		led_phut1 = off; 
			led_phut2 = on; P0 = so[dv_phut];		delay_ms(5); 		led_phut2 = off;
			led_giay1 = on; P0 = so[chuc_giay]; delay_ms(5);		led_giay1 = off;
			led_giay2 = on; P0 = so[dv_giay]; 	delay_ms(5); 		led_giay2 = off;
		}
	}

void main(){
	unsigned char  gio = 0, phut = 0, giay = 0;
	P3_0 = 0; 
	while(1){
		P3_0 = ~P3_0;
		giay ++;
		hienThi(gio, phut, giay); 
		if(giay==59) phut++;
		if(phut==59) gio++;
		if(hour == 0) {
			if(hour==0) gio++;
			delay_ms(50);
		}
		if(min == 0 )  {
			if(min==0) phut++;
			delay_ms(50);
		}
		if(second == 0)  {
			if(second==0) giay++;
			delay_ms(50);
		}
		if(phut>59)	phut = 0;
		if(giay>59) giay = 0;
		if(gio>23) gio = 0;
	}
	
}
	