#pragma once

#include <stddef.h>

void *memset(void *ptr, int value, size_t size);
void *memcpy(void *dest, const void *src, size_t size);
void *memmove(void *dest, const void *src, size_t size);
int memcmp(const void *a, const void *b, size_t size);