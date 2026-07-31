#include <stddef.h>
#include "lib/string.h"

void *memset(void *ptr, int value, size_t size) {
    unsigned char *p = ptr;

    while (size--) {
        *p++ = (unsigned char)value;
    }

    return ptr;
}

void *memcpy(void *dest, const void *src, size_t size) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (size--) {
        *d++ = *s++;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t size) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    
    if (d < s) {
        while (size--) { 
            *d++ = *s++; 
        }
    }
    else {
        d += size;
        s += size;

        while (size--) {
            *d-- = *s--;
        }
    }

    return dest;
}

int memcmp(const void *a, const void *b, size_t size) {
    const unsigned char *p1 = a;
    const unsigned char *p2 = b;

    while (size--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }

        p1++;
        p2++;
    }

    return 0;
}