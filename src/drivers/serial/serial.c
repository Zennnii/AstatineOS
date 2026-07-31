#include "arch/x86_64/io.h"

#define COM1_BASE 0x3F8

void serial_init(void) {
    // disable interrupts
    outb(COM1_BASE + 1, 0x00);

    // enable DLAB
    outb(COM1_BASE + 3, 0x80);

    // set baud rate to 115200
    outb(COM1_BASE + 0, 0x01); // low byte
    outb(COM1_BASE + 1, 0x00); // high byte

    // 8 bits no parity one stop bit
    outb(COM1_BASE + 3, 0x03);

    // enable FIFO
    outb(COM1_BASE + 2, 0xC7);

    // enable RTS/DSR
    outb(COM1_BASE + 4, 0x0B);
}

void serial_putchar(char c) {
    // wait until transmitter is empty
    while (!(inb(COM1_BASE + 5) & 0x20));

    outb(COM1_BASE, c);
}

void serial_write(const char *str){
    while (*str) {
        serial_putchar(*str++);
    }
}