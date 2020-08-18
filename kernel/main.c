#include "ns16550a.h"
#include "riscv.h"

int timer = 0;
void strap_vector();

int main() {
    uartinit();
    w_stvec((uint64)strap_vector);
    intr_on();
    int i = 0;
    while(1) {
        i++;
    }
    return 0;
}


void printime() {
    printf("Hello RISC-V %x\n", timer++);
}