#include <stdint.h>
#include "arch/x86_64/cpu/cpu.h"

<<<<<<< HEAD
=======
void hlt(void) {
    asm volatile ("hlt");
}

void cli(void) {
    asm volatile ("cli");
}

void sti(void) {
    asm volatile ("sti");
}

>>>>>>> 310d9ed13e1546b4283363d16acff34062825912
// halt the cpu indefinitely
void hcf(void) {
    cli();
    for (;;) {
        hlt();
    }
}

<<<<<<< HEAD
void hlt(void) {
    asm volatile ("hlt");
}

void cli(void) {
    asm volatile ("cli");
}

void sti(void) {
    asm volatile ("sti");
}

=======
>>>>>>> 310d9ed13e1546b4283363d16acff34062825912
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

<<<<<<< HEAD
uint64_t read_cr4(void) {
=======
uint64_t read_cr2(void) {
>>>>>>> 310d9ed13e1546b4283363d16acff34062825912
    uint64_t value;

    asm volatile (
        "mov %%cr4, %0"
        : "=r"(value)
    );

    return value;
}