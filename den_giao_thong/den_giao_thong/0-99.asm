	  org 00h

	  mov r5,#100
	  mov DPTR,#ma7thanh
naplai:	  mov r6,#0
lap:	  mov a,r6
	  cjne a,#99,hienthi
	  sjmp naplai

hienthi:
		mov b,#10
		div ab
;hang chuc
		setb p3.0
		movc a,@a+DPTR
		mov p2,a
		lcall delay
		clr p3.0

; hang don vi
		setb p3.1
		mov a,b
		movc a,@a+DPTR
		mov p2,a
		lcall delay
		clr p3.1

	  djnz r5,lap
	  inc r6
	  sjmp  lap

delay:
BACK:		mov r2,#2
		mov r1,#250
again:		djnz r1,again
		DJNZ R2,BACK
RET

ma7thanh:
DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,89H; Chuyen doi BCD

end