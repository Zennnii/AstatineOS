#include <stdint.h>
#include <stddef.h>
#include "init.h"
#include "arch/x86_64/x86_64_init.h"
#include "framebuffer.h"
#include "boot/limine_requests.h"
#include "arch/x86_64/io.h"
#include "drivers/serial/serial.h"

uint32_t *fb_ptr;
struct limine_framebuffer *fb;

void kernel_init(void) {
    serial_init();
    
    arch_init();

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        for (;;) { asm ("hlt"); }
    }

    fb = framebuffer_request.response->framebuffers[0];
    fb_ptr = (uint32_t *)fb->address;
}