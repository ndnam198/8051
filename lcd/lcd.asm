org 00h

mov a,#038h
acall comwrite

mov a,#0Eh
acall comwrite



mov a,#"D"
acall datawrite
mov a,#6h
acall comwrite

mov a,#"M"
acall datawrite
mov a,#14h
acall comwrite

mov a,#"V"
acall datawrite
mov a,#6h
acall comwrite

mov a,#"I"
acall datawrite
mov a,#6h
acall comwrite

mov a,#"E"
acall datawrite
mov a,#6h
acall comwrite


mov a,#"T"
acall datawrite

mov a,#0Fh
acall datawrite

here:
sjmp here



datawrite:
acall ready
mov p1,a
setb p2.0
clr p2.1
setb p2.2
clr p2.2
ret

comwrite:
acall ready
mov p1,a
clr p2.0
clr p2.1
setb p2.2
clr p2.2
ret 

ready: 
setb P1.7
clr P2.0
setb P2.1
back:

clr p2.2
setb p2.2
jb P1.7,back
ret 

end
		