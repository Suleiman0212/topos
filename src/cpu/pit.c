#include "pit.h"
#include "ports.h"

uint64_t ticks = 0;

void pit_initialize() {
  irq_install_handler(0, &pit_handler);

  uint32_t divisor = 1193180 / FREQUENCY;

  outb(0x43, 0x36);
  outb(0x40, (uint8_t)(divisor & 0xFF));
  outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

uint64_t pit_get_ticks() { return ticks; }

void pit_handler(InterruptRegisters *regs) {
  (void)regs;

  ticks++;
}
