#include "arch/x86_64/idt/isr.h"
#include "arch/x86_64/panic/panic.h"
#include "arch/x86_64/cpu/cpu.h"
#include "arch/cpu.h"
#include "lib/printf/printf.h"

// x86_64 specific panic
void x86_64_panic(const char *msg, const struct interrupt_frame *frame) {
    kprintf("Kernel panic!\n\n");
    kprintf("%s", msg);

    kprintf("Error code: %x\n", frame->error_code);
    kprintf("Vector: %d\n\n", frame->vector);

    kprintf("Regdump:\n");
    kprintf("RAX: %016lx\n", frame->rax);
    kprintf("RBX: %016lx\n", frame->rbx);
    kprintf("RCX: %016lx\n", frame->rcx);
    kprintf("RDX: %016lx\n", frame->rdx);
    kprintf("RBP: %016lx\n", frame->rbp);
    kprintf("RSI: %016lx\n", frame->rsi);
    kprintf("RDI: %016lx\n\n", frame->rdi);

    kprintf("R8: %016lx\n", frame->r8);
    kprintf("R9: %016lx\n", frame->r9);
    kprintf("R10: %016lx\n", frame->r10);
    kprintf("R11: %016lx\n", frame->r11);
    kprintf("R12: %016lx\n", frame->r12);
    kprintf("R13: %016lx\n", frame->r13);
    kprintf("R14: %016lx\n", frame->r14);
    kprintf("R15: %016lx\n\n", frame->r15);

    kprintf("CR0: %016lx\n", read_cr0());
    kprintf("CR2: %016lx\n", read_cr2());
    kprintf("CR3: %016lx\n", read_cr3());
    kprintf("CR4: %016lx\n", read_cr4());

    arch_halt_forever();
}