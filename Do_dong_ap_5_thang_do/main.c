#include <REGX51.H>
#include "port.h"
#include "LCD16x2.h"
#include "ADC0808.h"
#include "string.h"
#include "delay.h" 

int main(){
	ADC0808_Init();
	Lcd_Init();
	Lcd_Clear();
	while(1){
		Lcd_Out(0,0,"nothing really matter");
		Delay_ms(500);
		Lcd_Clear();
	}
}