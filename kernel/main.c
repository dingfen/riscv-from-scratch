#include "ns16550a.h"
#include "riscv.h"
#include "mm.h"
#include "dflib.h"

int timer = 0;
void strap_vector();

int main() {
    uartinit();
    
    initmm();

    w_satp(8L << 60 | KERNBASE >> 12);
    flushTLB();
    
    w_stvec((uint64)strap_vector);
    intr_on();

    procinit();
    idleproc();

    scheduler();
}


void printime() {
    printf("Hello RISC-V %x\n", timer++);
}