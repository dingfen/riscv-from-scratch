#include "mm.h"
#include "dflib.h"

// page table for kernel page space
// but how to make sure there are 512 PTEs space
// use malloc !!!
PageTable_t kernel_pagatable;
FreePage_t *kmem;

extern void strap_vector();

inline uint64 page_aligndown(uint64 addr) {
    return (addr & ~(PAGESIZE-1));
}

inline uint64 PA2PTE(uint64 pa) {
    return (pa >> PAGEOFF) << 10;
}

inline uint64 PTE2PA(uint64 pte) {
    return (pte >> 10) << PAGEOFF;
}

// build a free page link list
void initmm() {
    char *p = (char*)KERNEND;
    FreePage_t *pt;
    for(; p >= (char*)KERNBASE; p -= PAGESIZE) {
        pt = (FreePage_t *)p;
        pt->next = kmem;
        kmem = pt;
    }
    kernel_pagatable = (PageTable_t)kalloc();
    memset(kernel_pagatable, 0, PAGESIZE);
    map(kernel_pagatable, 0x2000000, 0x2000000, 0x10000, PTE_R | PTE_W);
    map(kernel_pagatable, 0x10000000, 0x10000000, 0x100, PTE_R | PTE_W);
    map(kernel_pagatable, 0x80000000, 0x80000000, 0x100000, PTE_X | PTE_R | PTE_W);
}

/** 
 * try to alloc a 4KB page
 * @return return a pointer to a new page. If no page anymore, return NULL
 */ 
void* kalloc() {
    FreePage_t *pt = kmem;
    if (kmem) {
        kmem = kmem->next;
    }
    return (void *)pt;
}

/**
 * try to dealloc a 4KB page
 */
void kfree(void *p) {
    FreePage_t *pt = (FreePage_t *)p;
    memset(pt, 0, PAGESIZE);
    pt->next = kmem;
    kmem = pt;
} 

inline int get_pagenum(int level, uint64 va) {
    int shift = PAGEOFF + level * 9;
    int mask = 0x1ff;
    return ((va >> shift) & mask);
}

// The risc-v Sv39 scheme has three levels of page-table pages.
// A page-table page contains 512 64-bit PTEs.
// A 64-bit virtual address is split into five fields:
//   39..63 -- must all equal to bit 38
//   30..38 -- 9 bits of level-2 index.
//   21..39 -- 9 bits of level-1 index.
//   12..20 -- 9 bits of level-0 index.
//    0..12 -- 12 bits of byte offset within the page.
PTE_t *virt2phys(PageTable_t table, uint64 va) {
    int level;
    PTE_t *pte;
    for(level = 2; level > 0; level--) {
        pte = &table[get_pagenum(level, va)];
        if (*pte & PTE_V) {
            // valid
            if (*pte & PTE_R || *pte & PTE_X) {
                // leaf
                break;
            } else {
                // non-leaf
                table = (PageTable_t)PTE2PA(*pte);
            }

        } else {
            if ((table = (PageTable_t)kalloc()) == 0)
                return NULL;
            memset(table, 0, PAGESIZE);
            *pte = PA2PTE((uint64)table) | PTE_V;
        }
    }
    return &table[get_pagenum(level, va)];
}

/**
 * @param table input, page table pointer
 * @param va    input, virtual address 
 * @param pa    input, physical address 
 * @param mode  PTE mode control
 * @return when map finished, the pa address will be mapped to va 
 * to visit pa just use va after paging
 */ 
void map(PageTable_t table, uint64 va, uint64 pa, uint64 size, uint64 mode) {
    uint64 pgstart = page_aligndown(va);
    uint64 pglast = page_aligndown(va + size-1);

    for(; pgstart <= pglast; pgstart += PAGESIZE, pa += PAGESIZE) {
        PTE_t *p = virt2phys(table, pgstart);
        *p = ((pa >> PAGEOFF) << 10) | PTE_V | mode;
    }
    return;
}