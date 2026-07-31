#include <stdint.h>
#include <stddef.h>
#include "video/framebuffer/framebuffer.h"
#include "boot/limine_requests.h"
#include "arch/x86_64/cpu/cpu.h"

void framebuffer_init(void) {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];

    framebuffer.address = fb->address;
    framebuffer.width = fb->width;
    framebuffer.height = fb->height;
    framebuffer.pitch = fb->pitch;
    framebuffer.bpp = fb->bpp;
}