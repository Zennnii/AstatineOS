#pragma once

#include <stdint.h>

struct __attribute__((packed)) gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
};

struct __attribute__((packed)) gdtr {
    uint16_t limit;
    uint64_t base;
};

void gdt_init(void);