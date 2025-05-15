#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include <stdbool.h>

void kernel_main(void) {
  // Initializing terminal
  terminal_initialize();

  // Reading data from serial
  serial_initialize();
}
