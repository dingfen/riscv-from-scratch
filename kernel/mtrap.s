# trap.s
# enabling the interrupt register in main 
##define an interrupt service routine
# setup a counter value
# wait for interrupt counts
# Interrupt occur
# save current register snapshot
# do the interrupt service routine (ISR) 
# restore register snapshot 
# back to main
.section .text
.global mtrap_vector




.align 4
mtrap_vector:
    nop                     # User Software Interrupt
    nop                     # Supervisor software Interrupt
    nop                     # 
    nop                     # Machine software Interrupt
    nop                     # User timer Interrupt
    nop                     # Supervisor timer Interrupt
    nop                     #
    j    mtimer             # Machine timer Interrupt



mtimer:
    addi sp, sp, -32
    sd   a0, 0(sp)
    sd   a1, 8(sp)
    sd   a2, 16(sp)
    sd   a3, 24(sp)
    
    # get the cause of interrupt or exception
    # to make sure it is mtimer
    csrr a1, mcause
    andi a1, a1, 0x3f   # get the last 7 bit
    li   a2, 7          # mtimer interrupt is 7
    beq  a1, a2, 1f
    j    3f
    

1:
    # handle timer interrupt
    # add mtimecmp
    la   a1, 0x2004000
    ld   a2, 0(a1)
    li   a3, 2000000
    add  a2, a2, a3
    sd   a2, 0(a1)
    
    # still need to be solved 
    # delegated to S-mode but it is weird
    # so i use software interrupt to process S-mode
	li   a1, 1 << 1
    csrw sip, a1
    # li   a1, 5 | (1<<63)
    # csrw scause, a1
    # csrr a2, mepc
    # csrw sepc, a2
    # la a2, strap_vector
    # csrw mepc, a2
    
    # use this if handle timer interrupt in M-mode
    # call printime

3:
    ld   a0, 0(sp)
    ld   a1, 8(sp)
    ld   a2, 16(sp)
    ld   a3, 24(sp)
  
    addi sp, sp, 32
    mret
