#include <REGX52.H>
#include<stdio.h>
void delay(int time){
		while(time--);
}

void main(){
	while(1){
	P0 = P2 = 0;
	delay(10000);
	P0 = P2 = 0xFF;
	delay(10000);
	}
}
	