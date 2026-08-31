#include <stdint.h>
#include "arch/x86_64/cpu/cpu.h"

// halt the cpu indefinitely
void hcf(void) {
    cli();
    for (;;) {
        hlt();
    }
}

void hlt(void) {
    asm volatile ("hlt");
}

void cli(void) {
    asm volatile ("cli");
}

void sti(void) {
    asm volatile ("sti");
}

uint64_t read_cr0(void) {
    uint64_t value;

    asm volatile (
        "mov %%cr0, %0"
        : "=r"(value)
    );

    return value;
}

uint64_t read_cr2(void) {
    uint64_t value;

    asm volatile (
        "mov %%cr2, %0"
        : "=r"(value)
    );

    return value;
}

uint64_t read_cr3(void) {
    uint64_t value;

    asm volatile (
        "mov %%cr3, %0"
        : "=r"(value)
    );

    return value;
}

uint64_t read_cr4(void) {
    uint64_t value;

    asm volatile (
        "mov %%cr4, %0"
        : "=r"(value)
    );

    return value;
}