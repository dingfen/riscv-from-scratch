# trap.s
# 
.section .text
.global rv_trap_vector

rv_trap_vector:
    # 
    mret
