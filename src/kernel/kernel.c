#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../cpu/pit.h"
#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include "../drivers/timer.h"
#include <stdbool.h>
#include <stdint.h>

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
  terminal_write_string("|-[@[C]normal @[R]&@[!]]-> \n");

  // Initilizing PIT
  pit_initialize();

  // OS loop
  timer_start();
  uint32_t last_second = 0;

  for (;;) {
    uint32_t elapsed = timer_get_elapsed_milliseconds();
    if (elapsed / 1000 > last_second) {
      last_second = elapsed / 1000;
      terminal_write_string("SECOND ELAPSED\n");
    }
  }
}
