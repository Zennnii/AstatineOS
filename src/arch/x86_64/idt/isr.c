#include <stddef.h>
#include "arch/x86_64/idt/isr.h"
#include "arch/x86_64/idt/isr_handlers.h"
#include "arch/x86_64/panic/panic.h"

void interrupt_handler(struct interrupt_frame *frame) {
    if (frame->vector < 32 && exception_handlers[frame->vector] != NULL) {
        exception_handlers[frame->vector](frame);
        return;
    }

    // handle interrupt with no specific handler
    x86_64_panic("Unhandled interrupt", frame);
}   