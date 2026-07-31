#pragma once

#include <stdint.h>

struct framebuffer {
    uint32_t *address;
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint16_t bpp;
};

extern struct framebuffer framebuffer;

void framebuffer_init(void);