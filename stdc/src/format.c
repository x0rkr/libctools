#define _POSIX_C_SOURCE 200809L
#include "libctools_std.h"
#include <string.h>

void println(const char *format, ...)
{
    // Thread safety lock: acquire standard output stream lock
    flockfile(stdout);

    if (format != NULL) {
        // OPTIMIZATION: "Fast-Path" checks if we can bypass the heavy vfprintf engine.
        // If there is no '%' in the string, we write the string directly and fast.
        if (strchr(format, '%') == NULL) {
            fputs_unlocked(format, stdout);
        } else {
            va_list args;
            va_start(args, format);
            vfprintf(stdout, format, args);
            va_end(args);
        }
    }

    // High performance newline insertion on the locked stream
    putchar_unlocked('\n');
    
    // Safety buffer flush: ensures instant display during crash reporting/piping
    fflush_unlocked(stdout);

    // Release the thread lock
    funlockfile(stdout);
}