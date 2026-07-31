#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "init.h"
#include "framebuffer.h"
#include "boot/limine_requests.h"
#include "drivers/serial/serial.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(6);

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void _start(void) {
    kernel_init();

    serial_write("Welcome to Astatine OS\n");

    hcf();
}