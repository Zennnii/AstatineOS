#include <stdint.h>
#include "arch/x86_64/idt/isr.h"
#include "arch/x86_64/idt/isr_handlers.h"
#include "arch/x86_64/cpu/cpu.h"
#include "lib/printf/printf.h"

void divide_error_handler(struct interrupt_frame *frame) {
    (void)frame;

    kprintf("#DE Divide Error\n");
    hcf();
}

void nmi_handler(struct interrupt_frame *frame) {
    (void)frame;

    kprintf("#NMI Non Maskable Interrupt\n");
    hcf();
}

void breakpoint_handler(struct interrupt_frame *frame) {
    (void)frame;

    kprintf("#BP Breakpoint\n");
    hcf();
}

void invalid_opcode_handler(struct interrupt_frame *frame) {
    (void)frame;

    kprintf("#UD Invalid Opcode (Undefined Opcode)\n");
    hcf();
}

void double_fault_handler(struct interrupt_frame *frame) {
    kprintf("#DF Double Fault\n");

    kprintf("Error code: %x\n", frame->error_code);
    kprintf("RIP: %x\n", frame->rip);
    kprintf("CS: %x\n", frame->cs);
    kprintf("RFLAGS: %x\n", frame->rflags);

    hcf();
}

void general_protection_handler(struct interrupt_frame *frame) {
    kprintf("#GP General Protection Fault\n");

    kprintf("Error code: %x\n", frame->error_code);
    kprintf("RIP: %x\n", frame->rip);
    kprintf("CS: %x\n", frame->cs);
    kprintf("RFLAGS: %x\n", frame->rflags);

    hcf();
}

void page_fault_handler(struct interrupt_frame *frame) {
    uint64_t address = read_cr2();

    kprintf("#PF Page Fault\n");

    kprintf("Error code: %x\n", frame->error_code);
    kprintf("Fault Address: %lx\n", address);  
    kprintf("RIP: %x\n", frame->rip);
    kprintf("CS: %x\n", frame->cs);
    kprintf("RFLAGS: %x\n", frame->rflags);
    
    hcf();
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