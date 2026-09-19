#pragma once

#include <stdint.h>

void hlt(void);
void cli(void);
void sti(void);

uint64_t read_cr0(void);
uint64_t read_cr2(void);
uint64_t read_cr3(void);
uint64_t read_cr4(void);