#ifndef _DF_RISCV_NS16550A_H
#define _DF_RISCV_NS16550A_H

#define REG_RHR  0  // read mode: Receive holding reg   
#define REG_THR  0  // write mode: Transmit Holding Reg
#define REG_IER  1  // write mode: interrupt enable reg
#define REG_FCR  2  // write mode: FIFO control Reg
#define REG_ISR  2  // read mode: Interrupt Status Reg
#define REG_LCR  3  // write mode:Line Control Reg
#define REG_MCR  4  // write mode:Modem Control Reg
#define REG_LSR  5  // read mode: Line Status Reg
#define REG_MSR  6  // read mode: Modem Status Reg


#define UART_DLL  0  // LSB of divisor Latch when enabled
#define UART_DLM  1  // MSB of divisor Latch when enabled

#define UART_BASE_ADDR  0x10000000L

volatile unsigned char *Reg(int reg);
unsigned char ReadReg(int reg);
void WriteReg(int reg, char c);

#endif // _DF_RISCV_NS16550A_H