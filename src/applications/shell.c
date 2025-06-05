#include "shell.h"

char typed_buffer[BUFFER_SIZE];
uint8_t typed_count = 0;

void type_shell() { terminal_write_string("\n|-[@[C]normal @[R]&@[!]]-> "); }

void command_help() { terminal_write_string("\nThere is no help.\n"); }

void command_clear() { terminal_clear(); }

void parse_command() {
  if (typed_count == 0) {
    type_shell();
    return;
  }

  if (strncmp(typed_buffer, "help", typed_count) == 0) {
    command_help();
  } else if (strncmp(typed_buffer, "clear", typed_count) == 0) {
    command_clear();
  } else {
    terminal_write_string("\n@[R]Error@[!]: invalid command!\n");
  }
  type_shell();
}

void type_ascii(char ascii) {
  typed_buffer[typed_count++] = ascii;
  terminal_write_char(ascii);
}

void parse_ascii(char ascii) {
  switch (ascii) {
  case '\n':
    parse_command();
    typed_count = 0;
    break;
  case '\b':
    if (typed_count > 0) {
      typed_count--;
      terminal_write_char('\b');
    }
    break;
  case '\t':
    typed_count += 3;
    type_ascii(ascii);
    break;
  default:
    type_ascii(ascii);
    break;
  }
}

void shell_run() {
  KeyboardKey key;
  int printable;
  char ascii;

  type_shell();
  while (true) {
    key = keyboard_read_key();

    printable = keyboard_key_to_ascii(key, keyboard_shift_pressed());
    if (printable == GAG_CHAR)
      continue;
    ascii = (char)(unsigned char)printable;
    parse_ascii(ascii);
  }
}
