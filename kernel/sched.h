/**
 * sched head file
 * mainly about task/process management and schedule
 */ 
#ifndef _DF_RISCV_SCHED_H
#define _DF_RISCV_SCHED_H

#define TASK_RUNNING		0
#define TASK_INTERRUPTIBLE	1
#define TASK_UNINTERRUPTIBLE	2
#define TASK_ZOMBIE		3
#define TASK_STOPPED		4

#ifndef NULL
#define NULL ((void *) 0)
#endif

#endif // _DF_RISCV_SCHED_H