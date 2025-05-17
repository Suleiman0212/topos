#include "../cpu/gdt.h"
#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include <stdbool.h>
#include <stdint.h>

// TODO:
// Create interrupt description table (IDT)
// Add interrupt requests (IRQ)

void kernel_main(void) {
  // Initilizing terminal and serial
  terminal_initialize();
  terminal_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal_clear();
  serial_initialize();
  terminal_write_string("Kernel started!\n");
  terminal_write_string("Terminal initialization...   [@[G]done@[!]]\n");
  terminal_write_string("Serial initialization...     [@[G]done@[!]]\n");

  // Initilizing GDT & IDT
  terminal_write_string("GDT & TSS initialization...  ");
  gdt_initialize();
  terminal_write_string("[@[G]done@[!]]\n");
}
