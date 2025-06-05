#include "pit.h"

uint64_t ticks_left = 0;

void pit_initialize() {
  irq_install_handler(0, &pit_handler);

  uint32_t divisor = 1193180 / FREQUENCY;

  outb(0x43, 0x36);
  outb(0x40, (uint8_t)(divisor & 0xFF));
  outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

void pit_cpu_sleep(uint64_t ms) {
  ticks_left = ms;
  while (ticks_left > 0) {
    asm("hlt");
  }
}

void pit_handler(InterruptRegisters *regs) {
  (void)regs;

  if (ticks_left > 0) {
    ticks_left -= 1;
  }
}
