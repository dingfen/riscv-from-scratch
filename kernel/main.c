int main() {
    uartinit();
    int i = 0;
    while(1) {
        i++;
    }
    return 0;
}


void printime() {
    char p[] = "Hello RISC-V \n";
    for(int i = 0; i < 15; i++)
        uartputc(p[i]);
}