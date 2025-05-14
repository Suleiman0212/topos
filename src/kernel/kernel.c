#include "../drivers/terminal.h"

void kernel_main(void) {
  terminal_initialize();
  terminal_write_string("Hello, World!\n");
}
