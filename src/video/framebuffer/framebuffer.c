#include <stdint.h>
#include <stddef.h>
#include "video/framebuffer/framebuffer.h"
#include "boot/limine_requests.h"
#include "arch/cpu.h"

struct framebuffer framebuffer;

void framebuffer_init(void) {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        arch_halt_forever();
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];

    framebuffer.address = fb->address;
    framebuffer.width = fb->width;
    framebuffer.height = fb->height;
    framebuffer.pitch = fb->pitch;
    framebuffer.bpp = fb->bpp;
}