#pragma once

[[noreturn]] void arch_halt_forever(void);

void arch_enable_interrupts(void);
void arch_disable_interrupts(void);