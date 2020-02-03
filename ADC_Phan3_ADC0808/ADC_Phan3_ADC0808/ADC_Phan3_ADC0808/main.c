#include "main.h"
#include "..\lib\delay.h"
#include "..\lib\lcd4.h"
#include "..\lib\ADC0808.h"

void main()
{
	unsigned char adc_value;
	unsigned int voltage;

	ADC0808_Init();
	Lcd_Init();

	//Lcd_Out(1,1,"Hello ");
	while(1)
	{
		adc_value = ADC0808_Read(1);

		Lcd_Chr(1,1,adc_value/100+0x30);
		Lcd_Chr_Cp(adc_value%100/10+0x30);
		Lcd_Chr_Cp(adc_value%10+0x30);

		voltage = adc_value * 19.61f;

		Lcd_Chr(2,1,voltage/1000+0x30);
		Lcd_Chr_Cp('.');
		Lcd_Chr_Cp(voltage%1000/100+0x30);
		Lcd_Chr_Cp(voltage%100/10+0x30);
		Lcd_Chr_Cp(voltage%10+0x30);

		Delay_ms(500);	 
	}
}

					   