
int main() {
    // char p[] = "hello!";
    // uartinit();
    // for(int i = 0; i < 6; i++)
    //     uartputc(p[i]);
    while(1) {
        asm volatile("wfi");
    }
    return 0;
}