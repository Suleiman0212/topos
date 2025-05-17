#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include <stdbool.h>
#include <stdint.h>

// TODO:
// Create interrupt description table (IDT)
// Add interrupt requests (IRQ)

// clang-format off
const char* TOPOS_LOGO =
"$$$$$$$$\\                   $$$$$$\\   $$$$$$\\  \n"
"\\__$$  __|                 $$  __$$\\ $$  __$$\\ \n"
"   $$ | $$$$$$\\   $$$$$$\\  $$ /  $$ |$$ /  \\__|\n"
"   $$ |$$  __$$\\ $$  __$$\\ $$ |  $$ |\\$$$$$$\\  \n"
"   $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ | \\____$$\\ \n"
"   $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$\\   $$ |\n"
"   $$ |\\$$$$$$  |$$$$$$$  | $$$$$$  |\\$$$$$$  |\n"
"   \\__| \\______/ $$  ____/  \\______/  \\______/                      @[R]v0.0.1 ALPHA@[!]"
"                 $$ |                         \n"
"                 $$ |                         \n"
"                 \\__|                         \n";
// clang-format on

void kernel_main(void) {
  // Initilizing terminal and serial
  terminal_initialize();
  terminal_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal_clear();
  serial_initialize();
  terminal_write_string("Starting kernel...           [@[G]done@[!]]\n");
  terminal_write_string("Terminal initialization...   [@[G]done@[!]]\n");
  terminal_write_string("Serial initialization...     [@[G]done@[!]]\n");

  // Initilizing GDT & IDT
  terminal_write_string("GDT & TSS initialization...  ");
  gdt_initialize();
  terminal_write_string("[@[G]done@[!]]\n");
  terminal_write_string("IDT initialization...        ");
  idt_initialize();
  terminal_write_string("[@[G]done@[!]]\n");
  terminal_write_string("@[B]ALL SYSTEMS LOADED SUCCESFULL!@[!]");
  terminal_write_string("\n\n\n");
  terminal_write_string(TOPOS_LOGO);
  terminal_write_string("\n\n\n");
}
