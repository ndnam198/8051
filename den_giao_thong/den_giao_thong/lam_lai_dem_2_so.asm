; Ta co thoi gian den do sang bang thoi gian den xanh sang cong thoi gian den vang sang
; Thoi gian den do sang tu 00-30 la 31 giay
; Thoi gian den xanh sang tu 00-25 la 26 giay
; suy ra thoi gian den vang sang la 31-26=5 giay hay tu 00-04
org 00h		; bat dau chuong trinh
mov DPTR, #ma7thanh	 ; nap ma led 7 thanh vao thanh ghi DPTR


chedo1:
lcall delay	; tao tre giua giay 00 cua den vang va giay 30 cua den do tren duong 1
mov r5,#223	; so lan quet led doi voi moi mot so
mov r6,#30	; thoi gian bat den do luu trong r6
mov r1,#25	; thoi gian bat den xanh luu trong r1
mov r7,#4	; thoi gian bat den vang luu trong r7
chaychedo1:	; tao vong lap de thuc hien che do 1
mov a,r1	; nap lai thoi gian cho den xanh de kiem tra dieu kien nhay sang che so 2 
cjne a,#-1,congviec1; den xanh nhay den -1 thi chuyen sang che do 2 neu khong thi di vao hienthi1 de thuc hien cong viec
sjmp chedo2		   ; nhay sang che so 2


congviec1: ; bat den do duong 1 va den xanh duong 2 va dem giay

setb	p3.1; bat den do duong 1
setb	p3.3; bat den xanh duong 2
clr 	p3.0 ; tat cac den con lai
clr		p3.2
clr		p3.4
clr		p3.5

;hien thi led 7 thanh duong 1
;hien thi so hang chuc 
mov a,r6
mov b,#10
div ab
movc a,@a+DPTR
setb p1.1
mov p0,a
lcall delay
clr p1.1

;hien thi so hang don vi
setb p1.0
mov a,b
movc a,@a+DPTR
mov p0,a
lcall delay
clr p1.0

; hien thi led 7 thanh duong 2
; hien thi so hang chuc
mov a,r1
mov b,#10
div ab
movc a,@a+DPTR
setb p1.3
mov p2,a
lcall delay
clr p1.3

; hien thi so hang don vi
setb p1.2
mov a,b
movc a,@a+DPTR
mov p2,a
lcall delay
clr p1.2


djnz r5,chaychedo1 ; quet led
dec r6			   ; giam thoi gian den do sang di 1 don vi
dec r1			   ; giam thoi gian den xanh sang di 1 don vi
sjmp chaychedo1


chedo2:
lcall delay		; tao do tre giua giay 05 voi giay 04 cua den do duong 1
chaychedo2:		; tao vong lap de thuc hien che do 2 
mov a,r7		; nap lai thoi gian sang den vang de kiem tra dieu kien nhay sang che so 3
cjne a,#-1,congviec2; thuc hien hien cong viec 2 cho den khi den vang = 00
mov r1,#25	 ; nap lai thoi gian den xanh bat dau chay truoc khi vao cho che do 3
mov r6,#30	 ; nap lai thoi gian den do bat dau chay truoc khi vao che do 3
sjmp chedo3	 ; nhay vao che do 3


congviec2:	 ; bat den do duong 1 va den vang duong 2 trong 5s va dem giay

setb	p3.1 ; bat den do duong 1
setb	p3.5 ; bat den vang duong 2
clr 	p3.0 ; tat cac den con lai
clr		p3.2
clr		p3.4
clr		p3.3

; hien thi thoi gian tren duong 1
; hien thi so hang chuc
mov a,r6
mov b,#10
div ab
movc a,@a+DPTR
setb p1.1
mov p0,a
lcall delay
clr p1.1
; hien thi so hang don vi
setb p1.0
mov a,b
movc a,@a+DPTR
mov p0,a
lcall delay
clr p1.0

; hien thi thoi gian duong 2
; hien thi so hang chuc
mov a,r7
mov b,#10
div ab
movc a,@a+DPTR
setb p1.3
mov p2,a
lcall delay
clr p1.3
;hien thi so hang don vi
setb p1.2
mov a,b
movc a,@a+DPTR
mov p2,a
lcall delay
clr p1.2


djnz r5,chaychedo2 ; quet led
dec r6			   ; giam thoi gian den do
dec r7			   ; giam thoi gian den vang
sjmp chaychedo2	   ; nhay vao chaychedo2

chedo3:
lcall delay		   ; tao thoi gian tre giua giay thu 00 cua den do duong 1 voi giay 25 den xanh duong 1
chaychedo3:        ; tao vong lap thuc hien che do 3 
mov a,r6		   ; nap lai gia tri den do de kiem tra dieu kien nhay den che do 4
cjne a,#4,congviec3; thuc hien cong viec 3 den khi gia tri den do bang 4
mov r7,#4		   ; nap lai thoi gian den vang duong1 bat dau chay truoc khi vao che do 4
mov r6,#5		   ; nap lai thoi gian den do duong 2 bat dau chay truoc kho vao che do 4
sjmp chedo4		   ; nhay vao che do 4


congviec3:         ; bat den xang duong 1 va den do duong 2 trong 25 giay va dem giay
setb	p3.0	   ; bat den xanh duong 1
setb	p3.4	   ; bat den do duong 2
clr 	p3.1	   ; tat cac den con lai
clr		p3.2
clr		p3.3
clr		p3.5

;hien thi thoi gian duong 1
; hien thi so hang chuc
mov a,r1
mov b,#10
div ab
movc a,@a+DPTR
setb p1.1
mov p0,a
lcall delay
clr p1.1
;hien thi so hang don vi
setb p1.0
mov a,b
movc a,@a+DPTR
mov p0,a
lcall delay
clr p1.0

;hien thi thoi gian duong 2
; hien thi so hang chuc
mov a,r6
mov b,#10
div ab
movc a,@a+DPTR
setb p1.3
mov p2,a
lcall delay
clr p1.3
;hien thi so hang don vi
setb p1.2
mov a,b
movc a,@a+DPTR
mov p2,a
lcall delay
clr p1.2


djnz r5,chaychedo3 ;quet led
dec r6			  ; giam thoi gian den do
dec r1			  ;giam thoi gian den xanh
sjmp chaychedo3	  ; nhay vao chaychedo3

chedo4:
lcall delay; tao thoi gian tre giua giay 00 cua den xanh voi giay 04 cua den vang duong 1 
chaychedo4:; tao vong lap de thuc hien che do 4

mov a,r6  ; nap lai thoi gian den do de kiem tra dieu kien nhay vao che do 1
cjne a,#0,congviec4; thuc hien cong viec 4 cho den khi den do  chay ve 00
ljmp chedo1		   ; nhay ve che do 1


congviec4:; bat den vang duong 1 den do duong 2 trong 5 giay va dem giay
setb	p3.2; bat den vang duong 1
setb	p3.4; bat den do duong 2
clr 	p3.1; tat cac den con lai
clr		p3.0
clr		p3.3
clr		p3.5
;hien thi thoi gian duong 1
;hien thi so hang chuc
mov a,r7
mov b,#10
div ab
movc a,@a+DPTR
setb p1.1
mov p0,a
lcall delay
clr p1.1
;hien thi so hang don vi
setb p1.0
mov a,b
movc a,@a+DPTR
mov p0,a
lcall delay
clr p1.0

; hien thi thoi gian duong 2
; hien thi so hang chuc
mov a,r6
mov b,#10
div ab
movc a,@a+DPTR
setb p1.3
mov p2,a
lcall delay
clr p1.3
;hien thi so hang don vi
setb p1.2
mov a,b
movc a,@a+DPTR
mov p2,a
lcall delay
clr p1.2


djnz r5,chaychedo4	   ;quet led
dec r6				   ;giam thoi gian den do
dec r7				   ; giam thoi gian den vang
sjmp chaychedo4		   ; nhay vao chaychedo4


;========ham delay========
delay:
mov r3,#1
back: mov r0,#250
again:djnz r0,again
djnz r3,back
ret

ma7thanh:	DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,89H; Chuyen doi BCD
end




