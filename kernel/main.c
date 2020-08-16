#include "ns16550a.h"
#include "riscv.h"

int timer = 0;

int main() {
    uartinit();
    int i = 0;
    while(1) {
        i++;
    }
    return 0;
}


void printime() {
    printf("Hello RISC-V %x\n", timer++);
}