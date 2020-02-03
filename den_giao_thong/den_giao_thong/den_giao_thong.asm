;		  -------------------------------------------------------------------------------------
 ;----------------------------CHUONG TRINH DEN GIAO THONG------------------------------
 ;----------------------------Fosc= 12MHz----------------------------------------------
 ;-------------------------------------------------------------------------------------
  
 ;-------------Ten cac led 7 thanh
				HIENTHI1 DATA P0
				HIENTHI2 DATA P2
;----------------Ten led vang xanh do
				xanh1 bit P3.0
				do1 bit P3.1
				vang1 bit P3.2
				xanh2 bit P3.3
				do2 bit P3.4
				vang2 bit P3.5
;---------------BIT chon LED cac duong
				led1 bit P1.0
				led2 bit P1.1

;------------------Ten cac bien
				t DATA 0030H;
;--------------Bien thoi gian hien thi lED 7 thanh
				TG1 DATA 031H
				TG2 DATA 032H
;----------------Noi luu gia tri thoi gian
				Tx1 DATA 033H
				Tv1 DATA 034H
				Td1 DATA 035H
					
				Tx2	DATA 036H
				Tv2 DATA 037H
				Td2 DATA 038H

;---------------Ten bien trang thai den
				TT1 DATA 039H
				TT2 DATA 040h
;---------------BIEN LUU DU LIEU sau XU LY
				DATALED11 DATA 41H
				DATALED12 DATA 42H
				DATALED21 DATA 43H
				DATALED22 DATA 44H


				ORG 000H
				LJMP MAIN
				ORG 00BH
				LJMP TIME1S



				ORG 0030H
KHOITAO:		MOV TMOD, #01H
				SETB EA;
				MOV TH0, #0B1H
				MOV TL0, #0E0H
				SETB ET0
;----------------Gia tri dat cho cac duong theo nhu cau thuc te				
				MOV Tx1, #26
				MOV Tv1, #3
				MOV Td1, #30
				MOV Tv2, #3
				MOV Tx2, #26
				MOV Td2, #30
;---------------Tinh toan cac thong so dua vao du lieu dat				
				MOV A, Tx1;
				SETB C;
				ADDC A, Tv1
				MOV Td2, A;
				
				SETB C;
				MOV A, Td1
				SUBB A, Tv2
				MOV Tx2, A
;----------------Gia tri khoi tao cho cac duong
				MOV TT1, #0
				MOV TG1, Tx1	
				CLR Do1
				CLR vang1
				SETB Xanh1
				
				MOV TT2, #2
				MOV TG2, Td2
				CLR Xanh2
				CLR Vang2
				SETB Do2
				
				SETB TR0		
				MOV DPTR, #LEDOUT;
				RET



 ;-----------------------------------------DEM giay--------------------------------------------------
TIME1S: 		MOV TH0, #0B1H
				MOV TL0, #0E0H; nagt timer 20ms
				SETB TR0;	
				MOV A,t
				DEC t;
				CJNE A, #0, CONTINUE
;--------------sau 1s giay				
				MOV t, #50				
				ACALL DUONG1
				ACALL XULY1			
				ACALL DUONG2
				ACALL XULY2				
CONTINUE:		ACALL HIENTHI; tan so quet led la 50Hz
				RETI 


;-----------------------------Chuong tinh tinh giay duong so 1
				DUONG1: MOV A, TG1
						DEC TG1
						CJNE A, #0,CONTINUED1
						MOV A, TT1
						
						SANGVANG1:	CJNE A, #0, SANGDO1
									MOV TT1, #1
									CLR xanh1
									SETB vang1
									MOV TG1, Tv1
									SJMP CONTINUED1	
									
						SANGDO1:	CJNE A, #1, SANGXANH1
									MOV TT1, #2
									CLR vang1
									SETB do1
									MOV TG1, Td1
									SJMP CONTINUED1
						
						
						SANGXANH1: 	MOV TT1, #0
									CLR do1
									SETB xanh1
									MOV TG1, Tx1					
									
				CONTINUED1:	RET	
					
					
					
;-----------------------------Chuong tinh tinh giay duong so 2
				DUONG2: MOV A, TG2
						DEC TG2
						CJNE A, #0,CONTINUED2
						MOV A, TT2
						
						SANGVANG2:	CJNE A, #0, SANGDO2
									MOV TT2, #1
									CLR xanh2
									SETB vang2
									MOV TG2, Tv2
									SJMP CONTINUED2	
									
						SANGDO2:	CJNE A, #1, SANGXANH2
									MOV TT2, #2
									CLR vang2
									SETB do2
									MOV TG2, Td2
									SJMP CONTINUED2
						
						
						SANGXANH2: 	MOV TT2, #0
									CLR do2
									SETB xanh2
									MOV TG2, Tx2				
									
				CONTINUED2:	RET	
				
				
;-----------------Chuyen doi thoi gian sang ma BCD-----------------------------------	
XULY1:
;---------------hang chuc
				MOV A, TG1;
				MOV B, #10
				DIV AB
				MOVC A, @A+DPTR				
				MOV DATALED11, A
;---------------Hang don vi
				MOV A, B
				MOVC A, @A+DPTR				
				MOV DATALED12,A
				RET
				
				
XULY2:
;---------------hang chuc
				MOV A, TG2;
				MOV B, #10
				DIV AB
				MOVC A, @A+DPTR				
				MOV duong2,A
				SETB led21
				ACALL DELAY
				CLR led21
;---------------Hang don vi
				MOV A, B
				MOVC A, @A+DPTR				
				MOV duong2,A
				SETB led20
				ACALL DELAY
				CLR led20

				SJMP HIENTHI
				RET


;--------------------------------Chuong trinh hien thi so giay va den-------------------------------------
HIENTHI:		JB LED2, HIENTHILED1
				SJMP HIENTHILED2			
				HIENTHILED1:
				CLR LED2
				SETB LED1
				MOV HIENTHI1, DATALED11
				MOV HIENTHI2, DATALED21
				RET
				HIENTHILED2:
				CLR LED1
				SETB LED2
				MOV HIENTHI1, DATALED12
				MOV HIENTHI2, DATALED22
				RET
		
;--------------Chuong trinh chinh


MAIN: 		ACALL KHOITAO
			acall HIENTHI
	WAIT:	SJMP WAIT
	LEDOUT:	DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,89H; Chuyen doi BCD
			END;