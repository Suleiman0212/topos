#include "../drivers/serial.h"
#include "../drivers/terminal.h"
#include <stdbool.h>

// TODO:
// Add terminal tcrolling
// Improve terminal functionality
// Create global description table (GDT)
// Create interrupt description table (IDT)
// Add interrupt requests (IRQ)

// FIX:
// Update terminal newline functionality

void kernel_main(void) {
  // Initializing terminal
  terminal_initialize();

  // Reading data from serial
  serial_initialize();
}
