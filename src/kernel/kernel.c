#include "../drivers/serial.h"
#include "../drivers/terminal.h"

void kernel_main(void) {
  // Writing to terminal
  terminal_initialize();
  terminal_write_string("Hello, World!\n");

  // Writing to serial
  serial_initialize();
  serial_write_string("Hello, World!\n");

  // Reading char from serial
  char c = serial_read_char();
  terminal_write_char(c);
}
