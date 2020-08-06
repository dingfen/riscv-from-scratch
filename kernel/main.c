static char sg[] = "hello world!";

int main() {
    uartinit();
    for(int i = 0; i < 12; i++)
        uartputc(sg[i]);
    // while(1) {
    //     asm volatile("wfi");
    // }
    return 0;
}