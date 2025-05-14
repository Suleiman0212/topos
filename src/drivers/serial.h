#include "../cpu/ports.h"

#define PORT 0x3f8

int serial_initialize();
char serial_read_char();
// TODO: char *serial_read_string();
void serial_write_char(const char data);
void serial_write_string(const char *data);
