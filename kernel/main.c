static char sg[] = "hello world!";

int main() {
    uartinit();
    for(int i =0;i<12;i++)
        uartputc(sg[i]);
    return 0;
}