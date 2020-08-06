.section isrsec

.global timerservice

timerservice:
    add sp, sp, -16
    csrrw a0, mscratch, a0
    sw  a1, 0(a0)
    sw  a2, 4(a0)
    sw  a3, 8(a0)
    sw  a4, 12(a0)

    la  a1, 0x02004000  # mtimecmp
    lw  a2, 0(a1) 
    lw  a3, 4(a1)
    addi a4, a2, 1000
    sltu a2, a4, a2
    add a3, a3, a2
    sw a3, 4(a1)
    sw a4, 0(a1)

    lw  a4, 12(a0)    
    lw  a3, 8(a0)
    lw  a2, 4(a0)
    lw  a1, 0(a0)
    csrrw  a0, mscratch, a0
    add sp, sp ,16
    mret
