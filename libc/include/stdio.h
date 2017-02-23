#ifndef _STDIO_H
#define _STDIO_H

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *restrict format, ...);
int putchar(int ic);
int puts(const char *s);

#ifdef __cplusplus
}
#endif

#endif
