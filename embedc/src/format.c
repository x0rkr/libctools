#include "libctools_emb.h"
#include <stdio.h>  
#include <stdarg.h>

// A low-level helper loop to print integers character by character safely

static void putnbr_emb(int n)
{
    unsigned int num;

    if (n < 0)
    {
        putchar('-');
        num = (unsigned int)(-((long)n)); 
    }
    else
    {
        num = (unsigned int)n;
    }
    
    // Recursively strip off digits from right to left
    if (num >= 10)
    {
        putnbr_emb(num / 10);
    }
    putchar((num % 10) + '0'); 
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

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%' && format[i + 1] != '\0')
        {
            i++; // Move to the format specifier
            
            if (format[i] == 's')
            {
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                
                while (*str != '\0')
                {
                    putchar(*str++);
                }
            } 
            else if (format[i] == 'd')
            {
                int num = va_arg(args, int);
                putnbr_emb(num);
            }
            else if (format[i] == 'c')
            {
                
                int ch = va_arg(args, int);
                putchar(ch);
            }
            else if (format[i] == '%')
            {
                putchar('%');
            }
            else 
            {
                putchar('%');
                putchar(format[i]);
            }
        } 
        else 
        {
            putchar(format[i]);
        }
    }

    putchar('\n');
    va_end(args);
}