/**
 * my libs file
 * include util functions
 */

#ifndef _DF_LIB_H
#define _DF_LIB_H

#include <stdarg.h>

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

// string.c
char *strcpy(char * dst, const char * src);
int strlen(const char * s);
void memset(void *p, char value, unsigned size);

// print.c
int itoa(int num, char *str, int base);
int vsprintf(char * s, const char * fmt, va_list arg);
int sprintf(char * str, const char * fmt, ...);
int printf(const char *fmt, ...);

// proc.c
void *malloc(uint64 size);
void free(void *p);
void procinit();


#endif // _DF_LIB_H