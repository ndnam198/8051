#include "ADC0808.h"
#include "port.h"
#include <REGX51.H>

void ADC0808_Init()
{
 	START = 0;
	ALE = 0;
	OE = 0;	
}

unsigned char ADC0808_Read(unsigned char channel)
{
	unsigned char kq;

 	ADDA = channel & 0x01;
	ADDB = channel & 0x02;
	ADDC = channel & 0x04;

	ALE = 1;
	START = 1;
	ALE = 0;
	START = 0;

	while(EOC);
	while(!EOC);

	OE = 1;
	kq = DATA;
	OE = 0;

	return kq;
}