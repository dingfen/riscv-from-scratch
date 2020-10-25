/**
 * riscv.h head file
 * wrap the asm instruction to inline function
 * define some useful typename
 */ 
#ifndef _DF_RISCV_RISCV_H
#define _DF_RISCV_RISCV_H

#include "dflib.h"

static inline void w_stvec(uint64 x) {
  asm volatile("csrw stvec, %0" : : "r" (x));
}

/**
 * read/write register sie 
 */ 
static inline uint64 r_sie() {
  uint64 x;
  asm volatile("csrr %0, sie" : "=r" (x) );
  return x;
}

static inline void w_sie(uint64 x) {
  asm volatile("csrw sie, %0" : : "r" (x));
}


/**
 * read/write register sstatus
 */ 
static inline uint64 r_sstatus() {
  uint64 x;
  asm volatile("csrr %0, sstatus" : "=r" (x) );
  return x;
}

static inline void w_sstatus(uint64 x) {
  asm volatile("csrw sstatus, %0" : : "r" (x));
}


static inline void w_satp(uint64 x) {
  asm volatile("csrw satp, %0" : : "r"(x));
}

static inline void flushTLB() {
  asm volatile("sfence.vma zero, zero");
}

// enable device interrupts
static inline void intr_on() {
  w_sie(r_sie() | (1 << 9) | (1 << 5) | (1 << 1));
  w_sstatus(r_sstatus() | (1 << 1));
}

#endif // _DF_RISCV_RISCV_H