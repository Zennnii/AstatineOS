#include <stdint.h>
#include "arch/x86_64/x86_64_init.h"
#include "arch/x86_64/gdt/gdt.h"
#include "arch/x86_64/idt/idt.h"

void arch_init(void) {
    gdt_init();
    idt_init();
}