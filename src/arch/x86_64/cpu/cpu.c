#include "arch/x86_64/cpu/cpu.h"

void hcf(void) {
    asm volatile ("cli");
    for (;;) {
        asm volatile ("hlt");
    }
}