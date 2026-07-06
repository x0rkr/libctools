#define _POSIX_C_SOURCE 200809L
#include "libctools_std.h"

void println(const char *format, ...)
{
    va_list args;
    
    flockfile(stdout);
    
    if (format != NULL) {
        va_start(args, format);

	for (int i = 0; format[i] != '\0'; i++) {
		putchar_unlocked(format[i]);
	}
	
		
        va_end(args);
    }
    
    putchar_unlocked('\n');
    
    funlockfile(stdout);
}