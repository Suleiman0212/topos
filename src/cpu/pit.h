#pragma once

#include "../cpu/idt.h"
#include "ports.h"
#include <stdint.h>

#define FREQUENCY 1000 // 1 tick per 1ms

void pit_initialize();
void pit_cpu_sleep(uint64_t ms);
void pit_handler(InterruptRegisters *regs);
