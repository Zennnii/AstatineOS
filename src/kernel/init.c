#include <stdint.h>
#include <stddef.h>
#include "kernel/init.h"
#include "arch/init.h"
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