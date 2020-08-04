
.section .text
.global main

.section .data
msg:
    .ascii "hello world."


main:
    call uartinit
    la  a1, msg
    ld  a0, (a1)
    call uartputc
    bne tp, zero, busy
    

busy:
    wfi
    j busy
