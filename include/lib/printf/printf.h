#pragma once

#include <stdint.h>
#include <stdarg.h>

void kprintf(const char *fmt, ...);
void kvprintf(void (*putc)(char), const char *fmt, va_list args);