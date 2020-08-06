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
.global rv_trap_vector

rv_trap_vector:
    .4byte 0x80001000 
