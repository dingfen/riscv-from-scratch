#include "proc.h"

int nextpid;
Task task[NTASK];

extern PageTable_t kernel_pagatable;

/**
 * alloc memory
 * @param sz size of the allocating memory (Bytes)
 * @return pointer to alloc memory space
 */
void *malloc(uint64 sz) {

} 

/**
 * dealloc memory
 * @param p pointer to dealloc memory
 */
void free(void * p) {

} 

uint64 taskvm(int off) {
    return (uint64)(0x10001000 + off * 2*PAGESIZE);
}

uint64 taskpm(int off) {
    return (uint64)(0x81000000 + off * 2*PAGESIZE);
}

void procinit() {
    nextpid = 0;
    Task *t;
    for(t = task; t < &task[NTASK]; t++) {
        t->state = TASK_UNRUNNABLE;

        char *p = kalloc();
        map(kernel_pagatable, taskvm(t-task), taskpm(t-task), 2*PAGESIZE, PTE_R | PTE_W);
        t->stack_top = taskvm(t-task);
    }
    w_satp(8L << 60 | KERNBASE >> 12);
    flushTLB();
}

Task* alloc_proc() {
    Task *t;
    // alloc pid
    for(t = task; t < &task[NTASK]; t++) {
        if (t->state == TASK_UNRUNNABLE) {
            t->pid = nextpid++;
            break;
        }
    }
    // alloc pagetable
    PageTable_t table = (PageTable_t)kalloc();
    memset(table, 0, PAGESIZE);
    map(table, (uint64)table, 0x80000000, 0x100000, PTE_X | PTE_R | PTE_W);
    t->pagetable = table;
    return t;
}

void idleproc() {
    Task *p = alloc_proc();
    strcpy(p->name, "idle");
    p->state = TASK_RUNNING;
    task[p->pid] = *p;
}

void scheduler() {
    Task *t;
    while(1) {
        for(t = task; t < &task[NTASK]; t++) {
            if (t->state == TASK_RUNNING) {
                printf("hello\n");
            }
        }
    }
}