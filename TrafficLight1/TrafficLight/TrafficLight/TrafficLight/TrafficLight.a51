XANH_1 DATA 30h
DO_1 DATA 31h
VANG_1 DATA 32h
XANH_2 DATA 33h
DO_2 DATA 34h
VANG_2 DATA 35h
DV_1 DATA 36h
C_1 DATA 37h
DV_2 DATA 38h
C_2 DATA 39h
LED_X1 BIT P0.0
LED_V1 BIT P0.1
LED_D1 BIT P0.2
LED_X2 BIT P0.3
LED_V2 BIT P0.4
LED_D2 BIT P0.5
LED_C1 BIT P3.3
LED_DV1 BIT P3.2
LED_C2 BIT P3.1
LED_DV2 BIT P3.0

ORG 000H
LJMP MAIN

ORG 000BH
CLR TR0				;tat Timer
MOV TL0, #0AFH		;set thoi gian dem 50000
MOV TH0, #03CH		;tuong duong voi 50ms
INC R2				;tang r2 20 lan de co duoc tre 1s
SETB TR0			;bat Timer
RETI

ORG 0030H
MAIN:
MOV TMOD, #01H		;su dung timer 0, mode 1
MOV TL0, #0AFH		;nap gia tri ban dau cho TL0,TH0 (k quan trong)
MOV TH0, #03CH
CLR TF0				;xoa co TF
MOV IE,#10000010B	;cho phep ngat timer 0
START:
;MOV P0,#00001100B	;bat den do 1 va xanh 2
MOV P0,#0
SETB LED_D1
SETB LED_X2
MOV XANH_1,#22		;nap cac gia tri dau cho xanh,do,vang
MOV DO_1,#25
MOV VANG_1,#3
MOV XANH_2,#22
MOV DO_2,#25
MOV VANG_2,#3

SHOW_D1_X2:
SETB TR0			;khoi dong bo timer
MOV R0,DO_1			;nap thoi gian den do vao R0
MOV R1, XANH_2		;nap thoi gian den xanh vao R1
LCALL TACHSO		;thuc hien tach so trong cac thanh ghi R0 va R1
MOV R2, #0			;xoa R2
AGAIN_1:
LCALL HIENTHI		;hien thi cac gia tri ra led
CJNE R2,#18,AGAIN_1	;dung vong lap de tao tre 1s dong thoi quet LED lien tuc 
DEC DO_1			;sau moi vong lap giam gia tri hien thi di 1
DEC XANH_2
DJNZ R1,SHOW_D1_X2
CLR LED_X2
SETB LED_V2
;MOV P0,#00010100B	;hien thi den do 1 va vang 2
SHOW_D1_V2:
MOV R1,VANG_2
MOV R0,DO_1
LCALL TACHSO
MOV R2,#0			;thuc hien tuong tu cac thao tac o tren
AGAIN_2:
LCALL HIENTHI
CJNE R2,#18,AGAIN_2
DEC DO_1
DEC VANG_2
DJNZ R1,SHOW_D1_V2
CLR LED_D1
CLR LED_V2
SETB LED_X1
SETB LED_D2
;MOV P0,#00100001B	;hien thi den do 2 va xanh 1

SHOW_D2_X1:
MOV R0,XANH_1
MOV R1,DO_2
LCALL TACHSO
MOV R2,#0			;thuc hien tuong tu cac thao tac o tren
AGAIN_3:
LCALL HIENTHI
CJNE R2,#18,AGAIN_3
DEC DO_2
DEC XANH_1
DJNZ R0,SHOW_D2_X1
CLR LED_X1
SETB LED_V1
;MOV P0,#00100010B	;hien thi den do 2 va vang 1

SHOW_D2_V1:
MOV R0,VANG_1
MOV R1,DO_2
LCALL TACHSO
MOV R2,#0			;thuc hien tuong tu cac thao tac o tren
AGAIN_4:
LCALL HIENTHI
CJNE R2,#18,AGAIN_4
DEC DO_2
DEC VANG_1
DJNZ R0,SHOW_D2_V1
CLR LED_V1
CLR LED_D2

LJMP START			;quay lai thuc hien tu dau
;-----------------------
TACHSO:			;tach cac so trong thanh ghi R0 va R1
MOV A,R0		;tach bien 1
MOV B,#10		;chia bien 1 cho 10, hang chuc luu vao C_1 hang don vi luu vao DV_1
DIV AB
MOV C_1, A
MOV A,B
MOV DV_1,A
MOV A,R1		;tach bien 2
MOV B,#10		;chia bien 2 cho 10, hang chuc luu vao C_2 hang don vi luu vao DV_2
DIV AB
MOV C_2, A
MOV A,B
MOV DV_2,A
RET
;-----------------------
HIENTHI:		;hien thi lan luot cac LED su dung chan P1
MOV DPTR,#MALED

SETB LED_DV1
MOV A,DV_1
MOVC A, @A + DPTR
MOV P1,A
LCALL DELAY
CLR LED_DV1

SETB LED_C1
MOV A,C_1
MOVC A, @A + DPTR
MOV P1,A
LCALL DELAY
CLR LED_C1

SETB LED_DV2
MOV A,DV_2
MOVC A, @A + DPTR
MOV P1, A
ACALL DELAY
CLR LED_DV2

SETB LED_C2
MOV A, C_2
MOVC A, @A + DPTR
MOV P1, A
ACALL DELAY
CLR LED_C2
RET
;------------------------
DELAY:
MOV R7, #5
DELAY_1: MOV R6, #100
DELAY_2: DJNZ R6, DELAY_2
DJNZ R7, DELAY_1
RET
;------------------------
DL_LED:
MOV R5,#0FFH
DJNZ R5,$
RET
;------------------------
MALED:
DB 0C0H, 0F9H, 0A4H, 0B0H, 099H, 092H, 082H, 0F8H, 080H, 090H
END



