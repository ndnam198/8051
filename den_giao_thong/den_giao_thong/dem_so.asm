org 00h
mov DPTR, #ma7thanh
mov r5,#100
chaylai:
mov r6,#30
mov r1,#25
lap:
dem30:
mov a,r6
cjne a,#-1,dem25
mov r6,#30
dem25: 
mov a,r1
cjne a,#-1,hienthi
mov r1,#25


hienthi:
hienthidem30:

mov a,r6
mov b,#10
div ab
movc a,@a+DPTR
setb p1.1
mov p0,a
lcall delay
clr p1.1

setb p1.0
mov a,b
movc a,@a+DPTR
mov p0,a
lcall delay
clr p1.0
hienthidem25:
mov a,r1
mov b,#10
div ab
movc a,@a+DPTR
setb p1.3
mov p2,a
lcall delay
clr p1.3

setb p1.2
mov a,b
movc a,@a+DPTR
mov p2,a
lcall delay
clr p1.2


djnz r5,lap
dec r6
dec r1
sjmp lap

delay:
mov r3,#3
back: mov r0,#25
again:djnz r0,again
djnz r3,back
ret
ma7thanh:	DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,89H; Chuyen doi BCD
end




