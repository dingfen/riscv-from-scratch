.option norvc
.section .data
msg:
    .ascii "hello"

.section .init,"ax"
.global _start
_start:
    # read our hart identifier into t0
    # see if it is 0 if not to busy loop
    csrr t0, mhartid
    bnez t0, 4f

    # SATP should be 0 Supervisor Address Translation and Protection
    csrw satp, zero
    .option push
    .option norelax
    
    la   gp, __global_pointer$

    .option pop

    # BSS section expected to be 0
    la  a0, __bss_start
    la  a1, __bss_end

    bgeu a0, a1, 2f
l1:
    sd   zero, (a0)
    addi a0, a0, 8
    bltu a0, a1, l1
2:
#     mv   a0, gp
#     la   a1, flash_sdata
#     la   a2, data_size
#     beqz a2, 3f
# l2:
#     ld   t0, (a1)
#     sd   t0, (a0)
#     addi a0, a0, 8
#     addi a1, a1, 8
#     addi a2, a2, -8
#     bgtz a2, l2

3:
    li   t5, 0xffff
    csrw medeleg, t5
    csrw mideleg, t5
    la   sp, __stack_top
    li   t0, (0b11 << 11) | (1 << 7) | (1 << 3)
    csrw mstatus, t0
    la   t1, main
    csrw mepc, t1
    la   t2, rv_trap_vector
    csrw mtvec, t2
    li   t3, (1 << 3) | (1 << 7) | (1 << 11)
    csrw mie, t3
    la   ra, 4f
    mret

4:
    wfi
    j 4b
