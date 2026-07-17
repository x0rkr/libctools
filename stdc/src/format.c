#define _POSIX_C_SOURCE 200809L
#include "libctools_std.h"

void println(const char *format, ...)
{
    flockfile(stdout);
    
    if (format != NULL) {
        va_list args;
        va_start(args, format);

        // vfprintf handles %s, %d, etc., safely inside your locked stdout stream!
        vfprintf(stdout, format, args);
        
        va_end(args);
    }
    
    putchar_unlocked('\n');
    funlockfile(stdout);
}