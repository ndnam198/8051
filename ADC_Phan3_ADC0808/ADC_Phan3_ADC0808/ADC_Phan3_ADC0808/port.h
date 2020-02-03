#ifndef _PORT_H_
#define _PORT_H_

// Khai bao ket noi voi LCD
sbit LCD_RS	= P0^0;
sbit LCD_EN	= P0^1;
sbit LCD_D4	= P0^4;
sbit LCD_D5 = P0^5;
sbit LCD_D6 = P0^6;
sbit LCD_D7 = P0^7;

// Khai bao ket noi voi ADC0808
#define ADC0808_DATA P3
sbit ADC0808_ADDA = P2^0;
sbit ADC0808_ADDB = P2^1;
sbit ADC0808_ADDC = P2^2;
sbit ADC0808_ALE  = P2^3;
sbit ADC0808_START = P2^4;
sbit ADC0808_EOC  = P2^5;
sbit ADC0808_OE   = P2^6;

#endif