Org 00h
Sjmp MAIN
Org 0023h 
Sjmp SERIAL
Org 30h
MAIN:
Mov tmod,#20h ; ch?n timer 1 mode 2 là 8 bit auto reload
Mov scon, #50h  ; ch?n mode 1 và enable nh?n d? li?u
Mov th1, #0FDh  ; ch?n baudrate = 9600bps
Mov ie, #10010000B  ; enable ng?t n?i ti?p và ng?t all
Setb tr1			; kh?i ch?y timer 1
HERE:
Sjmp HERE		; nh?y ??i ng?t

SERIAL:			; ch??ng trình ng?t
Jb ri, clear1			; ki?m tra c? nh?n
Mov a, sbuf			; chuy?n d? li?u nh?n ?c vào thanh ghi a
Cjne a,#60h, next		; so sánh kí t? v?a nh?n v?i giá tr? 60h
Next:
Jb cy, upper			; n?u cy>1 thì ký t? là ch? th??ng và c?n vi?t hoa
Jnb cy, lower     			; n?u cy=0 thì ký t? là ch? hoa c?n ph?i vi?t th??ng
Mov sbuf, a			;
Clr ti				; xóa c? truy?n

Clr ri

Clear1:
Clr ri
Clr ti
reti

UPPER:
Clr cy		; clr c? nh?
subb a, #20h ; chuy?n hoa kí t?
ret
LOWER:
Clr CY
add A,#20h	; chuy?n ký t? v? ch? th??ng
ret
end
