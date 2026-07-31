#include <stdint.h>
#include <stdbool.h>
#include "arch/x86_64/gdt/gdt.h"
#include "drivers/serial/serial.h"
#include "lib/printf/printf.h"

struct gdt_entry gdt_entries[5];
struct gdtr gdtr;

extern void gdt_flush(struct gdtr *gdtr);

void encodeGdtEntry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_mid = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);

    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= flags << 4;

    gdt_entries[num].access = access;
}

bool gdt_verify(void) {
    struct gdtr current;

    asm volatile ("sgdt %0" : "=m"(current));

    if (current.base != (uint64_t)&gdt_entries) {
        return false;
    }
    else if (current.limit != sizeof(gdt_entries) - 1) {
        return false;
    }

    return true;
}

void initGdt(void) {
    encodeGdtEntry(0, 0, 0x00000000, 0x00, 0x0);    // null descriptor
    encodeGdtEntry(1, 0, 0xFFFFF, 0x9A, 0xA);       // kernel mode code segment
    encodeGdtEntry(2, 0, 0xFFFFF, 0x92, 0xC);       // kernel mode data segment
    encodeGdtEntry(3, 0, 0xFFFF, 0xFA, 0xA);        // user mode code segment
    encodeGdtEntry(4, 0, 0xFFFF, 0xF2, 0xC);        // user mode data segment

    gdtr.limit = sizeof(gdt_entries) - 1;
    gdtr.base = (uint64_t)&gdt_entries;

    gdt_flush(&gdtr);

    if (gdt_verify()) {
        kprintf("GDT verified successfully\n");
    }
    else {
        kprintf("GDT verification failed\n");
    }
}