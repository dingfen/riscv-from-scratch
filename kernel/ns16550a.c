#include "ns16550a.h"

inline volatile unsigned char *Reg(int reg) {
    return (volatile unsigned char *)(UART_BASE_ADDR+reg);
}

inline unsigned char ReadReg(int reg) {
    return (*(Reg(reg)));
}

inline void WriteReg(int reg, char c) {
    (*Reg(reg)) = c;
}

void uartinit() {
    WriteReg(REG_IER, 0x00);

    WriteReg(REG_LCR, 0x80);

    WriteReg(UART_DLL, 0x03);
    WriteReg(UART_DLM, 0x00);

    // set word length to 8-bits
    WriteReg(REG_LCR, 0x03);
    // enable FIFOs
    WriteReg(REG_FCR, 0x07);
    // enable receiver interrupts
    WriteReg(REG_IER, 0x01);
}

void uartputc(int c) {
    while(ReadReg(REG_LSR) & (1 << 5) == 0)
        ;
    WriteReg(REG_THR, c);
}

int uartgetc() {

}

