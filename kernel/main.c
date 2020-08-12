int timer = 0;

int main() {
    char s[64];
    uartinit();
    
    int i = 0;
    while(0) {
        i++;
    }
    sprintf(s, "abc = %x, %%%% and %d\n", 13, 13);
    printf(s);
    return 0;
}


void printime() {
    printf("Hello RISC-V %x\n", timer++);
}