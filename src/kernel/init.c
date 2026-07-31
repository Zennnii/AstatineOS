#include <stdint.h>
#include <stddef.h>
#include "init.h"
#include "arch/x86_64/x86_64_init.h"
#include "drivers/serial/serial.h"
#include "video/framebuffer/framebuffer.h"
#include "lib/printf/printf.h"

void kernel_init(void) {
    serial_init();
    kprintf("Serial initialized\n");
    
    arch_init();
    kprintf("Architecture initialized\n");

    framebuffer_init();
    kprintf("Framebuffer initialized\n");

    kprintf("Kernel initialization complete\n");
}