
int main() {
    uartinit();
    char c = 'A';
    c++;
    uartputc(c);

    return 0;
}