#pragma once

#include "arch/x86_64/idt/isr.h"

void x86_64_panic(const char *msg, const struct interrupt_frame *frame);