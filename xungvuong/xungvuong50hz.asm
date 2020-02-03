org 00h
sjmp main
org 0bh
sjmp isr
org 30h
main:
mov tmod, #01h
mov ie, #10000010B
mov th0, #220
mov tl0, #00h
setb p2.2
setb tr0
here:
sjmp here

isr:
cpl p2.2
mov th0, #220
mov tl0, #00h
reti
end
