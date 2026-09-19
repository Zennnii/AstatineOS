#include <stdint.h>
#include "arch/x86_64/idt/isr.h"
#include "arch/x86_64/idt/isr_handlers.h"
#include "arch/x86_64/panic/panic.h"

void divide_error_handler(struct interrupt_frame *frame) {
    (void)frame;

    x86_64_panic("#DE Divide Error\n", frame);
}

void nmi_handler(struct interrupt_frame *frame) {
    (void)frame;

    x86_64_panic("#NMI Non Maskable Interrupt\n", frame);
}

void breakpoint_handler(struct interrupt_frame *frame) {
    (void)frame;

    x86_64_panic("#BP Breakpoint\n", frame);
}

void invalid_opcode_handler(struct interrupt_frame *frame) {
    (void)frame;

    x86_64_panic("#UD Invalid Opcode (Undefined Opcode)\n", frame);
}

void double_fault_handler(struct interrupt_frame *frame) {
    x86_64_panic("#DF Double Fault\n", frame);
}

void general_protection_handler(struct interrupt_frame *frame) {
    x86_64_panic("#GP General Protection Fault\n", frame);
}

void page_fault_handler(struct interrupt_frame *frame) {
    x86_64_panic("#PF Page Fault\n", frame);
}

exception_handler_t exception_handlers[32] = {
    [0] = divide_error_handler,
    [3] = breakpoint_handler,
    [2] = nmi_handler,
    [6] = invalid_opcode_handler,
    [8] = double_fault_handler,
    [13] = general_protection_handler,
    [14] = page_fault_handler
};