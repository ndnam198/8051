#include <REGX51.H>
#define tat		1
#define	sang	0
char so[] = {0x40, 0x79, 0X24, 0X30, 0X19, 0X12, 0X02, 0X78, 0X00, 0X10}; // tuong ung 01,2,3,4,5,6,7,8,9
char maquet[] = {0x7F, 0xBF, 0XDF, 0XEF, 0XF7, 0XFB, 0XFD, 0XFE};  //chu so hang dv, chuc ,tram, ngan, chuc ngan, tram ngan, trieu, chuc trieu
unsigned char chuSo[7];			//so led muon hien thi
unsigned long dem, temp;		//temp bien tach cac chu so, 

void delay_ms(unsigned int ms)
{
 unsigned int x,y;
 for(x=0;x<ms;x++)
 for(y=0;y<=110;y++);
}

void delay(int time){
	while(time--);
}

void tachChuSo(unsigned long temp, int soLed){
	int i;
			for(i=0;i<soLed;i++){
				chuSo[i]=temp%10;	//sau khi tach se luu cac gia tri vao mang chuSo[]
				temp=temp/10;
			}
}

//----------------------------------------------------
void quetLed(int soLed){
	int i,j;
		for(i=0;i<25;i++){			// lap lai viec nay 25 lan de tang muc do luu anh trong mat
			for(j=0; j <soLed; j++){// lan luot hien thi tung led trong 100
				P2=maquet[j];					//enable led thu j
				P0=so[chuSo[j]];			//hien thi chu so tuong ung voi x10 
				delay(10);
				P2 = 0xff;						//vo hieu het cac led 
				}
		}
}
void main(){
//	int\ i;
//	P2=maquet[0];
//	for(i = 0; i < 10; i++){
//	P0= chuSo[i];
//		delay_ms(1000);
//	}
	while(1){
			for(dem = 0; dem <= 99999999; dem++){
			tachChuSo(dem,7);
			quetLed(7);
		}
	}
}