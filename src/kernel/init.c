#include <stdint.h>
#include <stddef.h>
#include "init.h"
#include "arch/x86_64/x86_64_init.h"
#include "drivers/serial/serial.h"
#include "video/framebuffer/framebuffer.h"

void kernel_init(void) {
    serial_init();
    serial_write("Serial initialized\n");
    
    arch_init();
    serial_write("Architecture initialized\n");

    framebuffer_init();
    serial_write("Framebuffer initialized\n");

    serial_write("Kernel initialization complete\n");
}