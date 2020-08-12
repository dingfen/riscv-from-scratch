#include <stdarg.h>

#include "ns16550a.h"

/**
 * @param num  input number to string
 * @param str  output string
 * @param base hex or dec
 * @return length of str
 */ 
int itoa(int num, char *str, int base) {
    int n;
    int i = 0;
    int j = 0;
    int digit;
    char tmpstr[16];
    // neg number add '-'
    if (num < 0) {
        str[i++] = '-';
        n = -num;
    } else {
        n = num;
    }
    // hex digits add '0x'
    if (base == 16) {
        str[i++] = '0';
        str[i++] = 'x';
    }
    while(n != 0) {
        digit = n % base;
        n = n / base;
        if (digit < 10) {
            tmpstr[j++] = digit + 0x30;
        } else {
            tmpstr[j++] = digit + 0x61 - 10;
        }
    }
    for(; j > 0;) {
        str[i++] = tmpstr[--j];
    }
    // zero number
    if (num == 0) {
        str[i++] = '0';
    }
    str[i] = '\0';
    return i;
}


int vsprintf(char * s, const char * fmt, va_list arg) {
    int i, j, c, d;
    int tmp;
    char *pt;
    char tmpstr[16];

    for(i = 0, j = 0; (fmt[i] & 0xff) != 0; i++) {
        c = fmt[i];
        // char put
        if (c != '%') {
            s[j++] = fmt[i];
            continue;
        } else {
            // %d %x %s and %% 
            d = fmt[++i] & 0xff;
            switch (d)
            {
            case 'd':
                tmp = va_arg(arg, int);
                tmp = itoa(tmp, tmpstr, 10);
                strcpy(&s[j], tmpstr);
                j += tmp;
                break;
            case 'x':
                tmp = va_arg(arg, int);
                tmp = itoa(tmp, tmpstr, 16);
                strcpy(&s[j], tmpstr);
                j += tmp;
                break;
            case 's':
                pt = va_arg(arg, char*);
                strcpy(&s[j], pt);
                j += strlen(pt);
                break;
            case '%':
                s[j++] = '%'; 
            default:
                break;
            }
        }
    }
    return j;
}

/**
 * 
 */ 
int sprintf(char * str, const char * fmt, ...) {
    va_list va;
    va_start(va, fmt);
    int len = vsprintf(str, fmt, va);
    va_end(va);
    return len;
}

/**
 * @param fmt the string format
 * @return return length of written chars if success 
 */ 
int printf(const char *fmt, ...) {
    va_list va;
    int i, j, c, d, tmp;
    char str[1024];
    char *pt;

    va_start(va, fmt);
    int len = vsprintf(str, fmt, va);

    for(i = 0; i < len; i++) {
        uartputc(str[i]);
    }

    va_end(va);
    return len;
}