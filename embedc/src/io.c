#include "libctools_emb.h"
#include <stdio.h>  // Used for putchar() to mock the hardware output on your PC

// A low-level helper loop to print integers character by character
static void putnbr_emb(int n)
{
    // Handle negative numbers manually
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    
    // Recursively strip off digits from right to left, printing them left to right
    if (n >= 10)
    {
        putnbr_emb(n / 10);
    }
    putchar((n % 10) + '0'); // Convert raw remainder integer into its ASCII character
}

void println(const char *format, ...)
{
    if (format == NULL)
    {
        putchar('\n');
        return;
    }

    va_list args;
    va_start(args, format);

    // Loop through the format string character by character
    for (int i = 0; format[i] != '\0'; i++)
    {
        // When we hit a format specifier '%'
        if (format[i] == '%' && format[i + 1] != '\0')
        {
            i++; // Increment pointer index to inspect the format token type
            
            if (format[i] == 's')
            {
                // Grab the next argument as a character pointer (string)
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                
                // Print the string character-by-character
                while (*str != '\0')
                {
                    putchar(*str++);
                }
            } 
            else if (format[i] == 'd')
            {
                // Grab the next argument as a standard signed integer
                int num = va_arg(args, int);
                putnbr_emb(num);
            }
            else 
            {
                // If it's an unrecognized or escaped character (like %%), just print the raw '%'
                putchar('%');
                putchar(format[i]);
            }
        } 
        else 
        {
            // If it's a completely normal character, just pass it straight out
            putchar(format[i]);
        }
    }

    // Every println must end with a clean line break
    putchar('\n');

    va_end(args);
}