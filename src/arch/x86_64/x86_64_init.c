#include <stdint.h>
#include "arch/x86_64/x86_64_init.h"
#include "arch/x86_64/gdt/gdt.h"

void arch_init(void) {
    initGdt();
}