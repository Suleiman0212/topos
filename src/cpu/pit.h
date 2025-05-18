#pragma once

#include "../cpu/idt.h"
#include <stdint.h>

#define FREQUENCY 1000 // 1 tick per 1ms

void pit_initialize();
uint64_t pit_get_ticks();
void pit_handler(InterruptRegisters *regs);
