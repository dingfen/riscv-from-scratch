
int main() {
    char p = 'h';
    uartinit();
    uartputc(p);
    p++;
    uartputc(p);
    return 0;
}