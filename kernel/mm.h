/**
 * mm.h file
 * used for page-based memory-management
 */
#ifndef _DF_RISCV_MM_H
#define _DF_RISCV_MM_H

#define KERNBASE 0x80101000
#define KERNEND  0x81000000

#define PAGESIZE 4096
#define PAGEOFF  12

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define PTE_V (1L << 0) // valid
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4) // 1 -> user can access

#include "riscv.h"

typedef struct FreePages {
	struct FreePages *next;
} FreePage_t;

typedef uint64  PTE_t;
typedef uint64 *PageTable_t;

void initmm();
void *kalloc();
void kfree(void *p);

uint64 page_aligndown(uint64 addr);
uint64 PA2PTE(uint64);
uint64 PTE2PA(uint64);

int get_pagenum(int level, uint64 va);
PTE_t* virt2phys(PageTable_t table, uint64 va);

void map(PageTable_t table, uint64 va, uint64 pa, uint64 size, uint64 mode);

#endif // _DF_RISCV_MM_H