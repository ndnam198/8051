c1 bit P1.0
c2 bit P1.1
c3 bit P1.2
c4 bit P1.3
h1 bit P0.0
h2 bit P0.1
h3 bit P0.2
h4 bit P0.3
E bit P3.2
RS bit P3.0
RW bit P3.1

org 00h
sjmp main
org 30h
main:
mov a,#38h 
acall comwrite
mov a,#0eh
acall comwrite
mov P1,#0Fh
clr c1
clr c2
clr c3
clr c4
here:
acall quetphim
sjmp here

quetphim:



PHIM0:
mov a,#'0'
acall datawrite
ret
PHIM1:
mov a,#'1'
acall datawrite
ret
PHIM2:
mov a,#'2'
acall datawrite
ret
PHIM3:
mov a,#'3'
acall datawrite
ret
PHIM4:
mov a,#'4'
acall datawrite
ret
PHIM5:
mov a,#'5'
acall datawrite
ret
PHIM6:
mov a,#'6'
acall datawrite
ret
PHIM7:
mov a,#'7'
acall datawrite
ret
PHIM8:
mov a,#'8'
acall datawrite
ret
PHIM9:
mov a,#'9'
acall datawrite
ret
PHIMA:
mov a,#'A'
acall datawrite
ret
PHIMB:
mov a,#'B'
acall datawrite
ret
PHIMC:
mov a,#'C'
acall datawrite
ret
PHIMD:
mov a,#'D'
acall datawrite
ret
PHIME:
mov a,#'E'
acall datawrite
ret
PHIMF:
mov a,#'F'
acall datawrite
ret

datawrite:
acall ready
mov p2,a
setb rs
clr rw
setb e 
clr e
ret

comwrite:
acall ready
mov p2,a
clr rs
clr rw
setb e
clr e
ret


ready:
setb P2.7
clr rs
setb rw
back:
clr e
setb e
jb P2.7, BACK
ret

end
