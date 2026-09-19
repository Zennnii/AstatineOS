#include <stdint.h>
#include "arch/cpu.h"
#include "lib/printf/printf.h"
#include "kernel/panic/panic.h"

[[noreturn]] void panic(const char *msg) {
    kprintf("Kernel panic!\n\n");
    kprintf("%s\n", msg);

    arch_halt_forever();
}