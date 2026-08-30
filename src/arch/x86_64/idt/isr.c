#include <stddef.h>
#include "arch/x86_64/idt/isr.h"
#include "arch/x86_64/idt/isr_handlers.h"
#include "arch/x86_64/cpu/cpu.h"
#include "lib/printf/printf.h"

void interrupt_handler(struct interrupt_frame *frame) {
    if (frame->vector < 32 && exception_handlers[frame->vector] != NULL) {
        exception_handlers[frame->vector](frame);
        return;
    }

    // handle interrupt with no specific handler
    kprintf("Unhandled interrupt: %d\n", frame->vector);

    kprintf("Error code: %x\n", frame->error_code);
    kprintf("RIP: %x\n", frame->rip);
    kprintf("CS: %x\n", frame->cs);
    kprintf("RFLAGS: %x\n", frame->rflags);

    hcf();
}   