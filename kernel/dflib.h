/**
 * my libs file
 * include util functions
 */

#ifndef _DF_LIB_H
#define _DF_LIB_H

#include <stdarg.h>

// string.c
char *strcpy(char * dst, const char * src);
int strlen(const char * s);
void memset(void *p, char value, unsigned size);

// print.c
int itoa(int num, char *str, int base);
int vsprintf(char * s, const char * fmt, va_list arg);
int sprintf(char * str, const char * fmt, ...);
int printf(const char *fmt, ...);


#endif // _DF_LIB_H