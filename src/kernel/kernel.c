#include "../applications/shell.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../cpu/pit.h"
#include "../drivers/keyboard.h"
#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include <stdbool.h>
#include <stdint.h>

// TODO: Rewrite the entire keyboard driver from scratch

void kernel_main(void) {
  // Initilizing Terminal
  terminal_initialize();
  terminal_clear();

  // Initilizing Serial;
  terminal_write_string("Starting kernel...           [@[G]done@[!]]\n");
  terminal_write_string("Terminal initialization...   [@[G]done@[!]]\n");
  terminal_write_string("Serial initialization...     [@[G]done@[!]]\n");

  // Initilizing GDT
  terminal_write_string("GDT & TSS initialization...  ");
  gdt_initialize();
  terminal_write_string("[@[G]done@[!]]\n");

  // Initilizing IDT
  terminal_write_string("IDT initialization...        ");
  idt_initialize();
  terminal_write_string("[@[G]done@[!]]\n");

  terminal_write_string("@[M]ALL SYSTEMS LOADED SUCCESFULL!@[!]");
  terminal_write_string("\n\n\n");
  terminal_write_string(TOPOS_LOGO);
  terminal_write_string("\n\n\n");
  terminal_write_string("|-[@[C]normal @[R]&@[!]]-> ");

  // Initilizing PIT
  pit_initialize();

  // Initilizing Keyboard
  keyboard_initialize();

  // Shell start
  shell_run();
}
