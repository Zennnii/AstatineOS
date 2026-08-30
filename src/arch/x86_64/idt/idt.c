#include <stdint.h>
#include <stdbool.h>
#include "arch/x86_64/cpu/cpu.h"
#include "arch/x86_64/idt/idt.h"
#include "arch/x86_64/idt/isr.h"
#include "lib/printf/printf.h"

struct idt_entry idt[256];
struct idtr idtr;

// Load the IDT
extern void idt_flush(struct idtr *idtr);

// array of ISR stubs indexed by interrupt vector
void (*isr_array[32])() = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
};

void idt_set_entry(uint8_t vector, void (*handler)(void), uint16_t selector, uint8_t ist, uint8_t type_attributes) {
    uint64_t offset = (uint64_t)handler;

    idt[vector].offset_low = (offset & 0xFFFF);
    idt[vector].offset_mid = (offset >> 16) & 0xFFFF;
    idt[vector].offset_high = (offset >> 32) & 0xFFFFFFFF;

    idt[vector].selector = selector;
    idt[vector].ist = ist;
    idt[vector].type_attributes = type_attributes;
    idt[vector].zero = 0;
}

bool idt_verify(void) {
    struct idtr current;

    asm volatile ("sidt %0" : "=m"(current));

    if (current.base != (uint64_t)idt) {
        return false;
    }
    else if (current.limit != sizeof(idt) - 1) {
        return false;
    }

    return true;
}

void idt_init(void) {
    idtr.base = (uint64_t)&idt;
    idtr.limit = sizeof(idt) - 1;

    for (int i = 0; i < 32; i++) {
        idt_set_entry(i, isr_array[i], 0x08, 0, 0x8E);
    }

    idt_flush(&idtr);

    // verify that the IDT was loaded correctly
    if (idt_verify()) {
        kprintf("IDT verified successfully\n");
    }
    else {
        kprintf("IDT verification failed\n");
        hcf();
    }
}