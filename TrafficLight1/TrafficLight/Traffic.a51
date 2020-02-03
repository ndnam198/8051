org 000H
sjmp main
org 0BH
    mov TH0,#0D8H
    mov TL0,#0EFH
    inc R0
    reti
xanh_1 equ 30H
do_1   equ 31H
xanh_2 equ 32H
do_2   equ 33H
vang   equ 34H

main:
    mov TMOD,#01
    mov TH0,#3CH
    mov TL0,#0AFH
    clr TF0
    setb TR0
    mov IE,#82H
start: 
    mov P0,#21H   ;xuat led do2 xanh1
    mov xanh_1,#25
    mov do_1,#36
    mov xanh_2,#33
    mov do_2,#28 
    mov vang,#3
    mov R1,xanh_1
    mov R2,do_2
loop_1: 
    mov R0,#0
    lcall chuyen_BCD
      
again_1:    
    lcall xuat_led
    cjne R0,#20,again_1
    dec R2
    djnz R1,loop_1
    mov P0,#22H  ;xuat led vang sang
    mov R1,vang
loop_2: mov R0,#0
    lcall chuyen_BCD
again_2: 
    lcall xuat_led
    cjne R0,#20,again_2
    dec R2
    djnz R1,loop_2
    mov P0,#0CH      ;xuat led xanh2 do 1 sang
    mov R1,do_1
    mov R2,xanh_2
loop_3: 
    mov R0,#0EFH
    lcall chuyen_BCD
again_3:  
    lcall xuat_led
    cjne R0,#20,again_3
    dec R1
    djnz R2,loop_3
    mov P0,#14H         ;vang2 sang
    mov R2,vang
loop_4:
    mov R0,#0
    lcall chuyen_BCD
again_4:   
    lcall xuat_led
    cjne R0,#20,again_4
    dec R2
    djnz R1,loop_4
      
    ljmp start
chuyen_BCD: 
    mov A,R1
    mov B,#10
    div AB
    mov 50H,A
    mov 51H,B
                                                  
    mov A,R2
    mov B,#10
    div AB
    mov 52H,A
    mov 53H,B
    
 xuat_led:
    mov DPTR,#123H
    mov A,50H
    movc A,@A+DPTR
    mov P2,A
    mov P3,#01H
    lcall delay
    mov P3,#00H

    mov A,51H
    movc A,@A+DPTR
    mov P2,A
    mov P3,#02H
    lcall delay
    mov P3,#00H

    mov A,52H
    movC A,@A+DPTR
    mov P1,A
    mov P3,#04H
    lcall delay
    mov P3,#00H
    
    mov A,53H
    movc A,@A+DPTR
    mov P1,A
    mov P3,#08H
    lcall delay
    mov P3,#00H
  
delay:  mov R6,#100
lap:   djnz R6,lap
        ret

org 123H
DB  0C0H,0F9H,0A4H,0B0H,099H,092H,082H,0F8H,080H,090H
end