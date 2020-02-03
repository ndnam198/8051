#include <REGX51.H>
#include "delay.h"
#include <REGX51.H>

void Delay_ms(unsigned int t)
	{
	 	unsigned int x, y;
		for(x = 0; x<t; x++)
		{
		 	for(y=0; y<113; y++);
		}
	}