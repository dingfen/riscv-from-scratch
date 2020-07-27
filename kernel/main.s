
.section .text
.global main



main:
    bne tp, zero, busy
    

busy:
    wfi
    j busy
