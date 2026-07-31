#include <stdarg.h>
#include <stdint.h>
#include "drivers/serial/serial.h"

void kprintf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    kvprintf(serial_putchar, fmt, args);

    va_end(args);
}

void kvprintf(void (*putc)(char), const char *fmt, va_list args) {
    while (*fmt) {
        if (*fmt != '%') {
            putc(*fmt);
            fmt++;
            continue;
        }

        fmt++; // skip %

        switch (*fmt) {
            // string
            case 's': {
                char *str = va_arg(args, char *);

                while (*str) {
                    putc(*str++);
                    
                }
            break;
            }
            // char
            case 'c': {
                char c = va_arg(args, char);
                putc(c);
                break;
            }
            // decimal
            case 'd': {
                int num = va_arg(args, int);
            
                if (num < 0) {
                    putc('-');
                    print_number(putc, (uint64_t)(-(int64_t)num), 10);
                } else {
                    print_number(putc, (uint64_t)num, 10);
                }
            
                break;
            }
            // hexadecimal
            case 'x': {
                unsigned int num = va_arg(args, unsigned int);
                print_number(putc, num, 16);
                break;
            }

            case '%':
                putc('%');
                break;
        }

        fmt++;
    }
}

static void print_number(void (*putc)(char), uint64_t value, unsigned int base) {
    static const char digits[] = "0123456789abcdef";
    char buffer[65];
    size_t i = 0;

    if (base < 2 || base > 16) {
        return;
    }

    if (value == 0) {
        putc('0');
        return;
    }

    while (value != 0) {
        unsigned int digit = value % base;
        buffer[i++] = digits[digit];
        value /= base;
    }

    while (i > 0) {
        putc(buffer[--i]);
    }
}