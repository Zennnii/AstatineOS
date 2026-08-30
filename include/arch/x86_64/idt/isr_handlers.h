#pragma once

#include "arch/x86_64/idt/isr.h"

typedef void (*exception_handler_t)(struct interrupt_frame *frame);

// exception handlers
void divide_error_handler(struct interrupt_frame *frame);
void nmi_handler (struct interrupt_frame *frame);
void breakpoint_handler (struct interrupt_frame *frame);
void invalid_opcode_handler (struct interrupt_frame *frame);
void double_fault_handler (struct interrupt_frame *frame);
void general_protection_handler (struct interrupt_frame *frame);
void page_fault_handler(struct interrupt_frame *frame);

// array holding all exception handlers
extern exception_handler_t exception_handlers[32];