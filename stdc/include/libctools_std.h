#ifndef LIBCTOOLS_STD_H
#define LIBCTOOLS_STD_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
//println()
void println(const char *format, ...);
//strreplace()
char *strreplace(const char *str, const char *old_sub, const char *new_sub);

#endif /* LIBCTOOLS_STD_H */

