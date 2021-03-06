/*
 * PLIC(Platform-Level Interrupt Controller) header file
 * init read/write reg 
 *
 */  
#ifndef _DF_RISCV_PLIC_H
#define _DF_RISCV_PLIC_H

// qemu puts programmable interrupt controller here.
#define PLIC 0x0c000000L
#define PLIC_PRIORITY   (PLIC + 0x0)
#define PLIC_PENDING    (PLIC + 0x1000)
#define PLIC_MENABLE    (PLIC + 0x2000)
#define PLIC_SENABLE    (PLIC + 0x2080)
#define PLIC_MPRIORITY  (PLIC + 0x200000)
#define PLIC_SPRIORITY  (PLIC + 0x201000)
#define PLIC_MCLAIM     (PLIC + 0x200004)
#define PLIC_SCLAIM     (PLIC + 0x201004)



#endif // _DF_RISCV_PLIC_H