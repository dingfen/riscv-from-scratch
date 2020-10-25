/**
 * sched head file
 * mainly about task/process management and schedule
 */ 
#ifndef _DF_RISCV_SCHED_H
#define _DF_RISCV_SCHED_H

#include "dflib.h"
#include "mm.h"

#define TASK_UNRUNNABLE  -1
#define TASK_RUNNING		0
#define TASK_INTERRUPTIBLE	1
#define TASK_UNINTERRUPTIBLE	2
#define TASK_ZOMBIE		3
#define TASK_STOPPED		4

#define NTASK 32

#ifndef NULL
#define NULL ((void *) 0)
#endif

// Saved registers for kernel context switches.
typedef struct Context {
  uint64 ra;
  uint64 sp;

  // callee-saved
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
} Context;


typedef struct TrapFrame {
    uint64 kernel_satp;   // kernel page table    /*   0 */
    uint64 kernel_sp;     // top of process's kernel stack    /*   8 */
    uint64 kernel_trap;   // usertrap()   /*  16 */
    uint64 epc;           // saved user program counter   /*  24 */
    uint64 kernel_hartid; // saved kernel tp    /*  32 */
    uint64 ra;    /*  40 */
    uint64 sp;    /*  48 */
    uint64 gp;    /*  56 */
    uint64 tp;    /*  64 */
    uint64 t0;    /*  72 */
    uint64 t1;    /*  80 */
    uint64 t2;    /*  88 */
    uint64 s0;    /*  96 */
    uint64 s1;    /* 104 */
    uint64 a0;    /* 112 */
    uint64 a1;    /* 120 */
    uint64 a2;    /* 128 */
    uint64 a3;    /* 136 */
    uint64 a4;    /* 144 */
    uint64 a5;    /* 152 */
    uint64 a6;    /* 160 */
    uint64 a7;    /* 168 */
    uint64 s2;    /* 176 */
    uint64 s3;    /* 184 */
    uint64 s4;    /* 192 */
    uint64 s5;    /* 200 */
    uint64 s6;    /* 208 */
    uint64 s7;    /* 216 */
    uint64 s8;    /* 224 */
    uint64 s9;    /* 232 */
    uint64 s10;   /* 240 */
    uint64 s11;   /* 248 */
    uint64 t3;    /* 256 */
    uint64 t4;    /* 264 */
    uint64 t5;    /* 272 */
    uint64 t6;    /* 280 */
    uint64 freg[32];    /* 288 */
} TrapFrame;

typedef struct Task {
    long state;         // -1 unrunnable  0 runnable  >0 stopped
    long priority;
    int pid;
    uint64 stack_top;
    PageTable_t pagetable;
    char name[16];      // process name for debugging
    Context *ctx;
    TrapFrame *tf;
} Task;

inline uint64 taskvm(int off);
inline uint64 taskpm(int off);
void procinit();
Task* alloc_proc();
void idleproc();
void scheduler();

#endif // _DF_RISCV_SCHED_H