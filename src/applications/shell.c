#include "shell.h"
#include "../drivers/keyboard.h"
#include "../drivers/terminal.h"
#include "../util/str.h"
#include <stdbool.h>
#include <stdint.h>

uint8_t typed_count;

void parse_input(char *buffer) {
  if (strcmp("help", buffer) == 0) {
    terminal_write_string("\n\nCommands:\n\t@[B]help@[!] - to show "
                          "this\n\t@[B]topos@[!] - to show "
                          "OS info\n\t@[B]clear@[!] - to clear terminal\n");
  } else if (strcmp("topos", buffer) == 0) {
    terminal_write_string("\n\n\n");
    terminal_write_string(TOPOS_LOGO);
    terminal_write_string("\n");
    terminal_write_string(
        "@[R]ABSOLUTE NO WARRANTY. USE AT YOUR OWN RISK.\n@[!]TOPOS "
        "IS A X86 OPERATING SYSTEM DEVELOPED BY @[B]SULEIMAN "
        "KIRIMOV@[!] IN @[G]2025@[!].\n");
  } else if (strcmp("clear", buffer) == 0) {
    terminal_clear();
  } else if (typed_count > 0) {
    terminal_write_string("\n @[R]Error@[!]: Unknown command!");
  } else {
    return;
  }
}

void shell_run() {
  char typed_buffer[256];
  typed_count = 0;
  typed_buffer[0] = '\0';

  while (true) {
    KbPhysicalKey key = keyboard_read_phys_key();
    int cch;
    char ch;
    switch (key) {
    case KB_PHYS_KEY_ESC:
      terminal_clear();
      ch = '\n';
      break;
    case KB_PHYS_KEY_INSERT:
      parse_input("help");
      ch = '\n';
      break;
    default:
      cch = keyboard_phys_key_to_char(key, keyboard_shift_pressed(key));
      if (cch != GAG_CHAR)
        ch = (char)(unsigned char)cch;
      else
        return;
      break;
    }

    switch (ch) {
    case '\n':
      typed_buffer[typed_count] = '\0';
      char *trimmed = typed_buffer;
      while (*trimmed == ' ')
        trimmed++;
      parse_input(trimmed);
      terminal_write_string("\n|-[@[C]normal @[R]&@[!]]-> ");
      typed_count = 0;
      typed_buffer[0] = '\0';
      break;
    case '\b':
      if (typed_count > 0) {
        typed_count--;
        terminal_write_string("\b");
      }
      break;
    case '\t':
      typed_count += 3;
    default:
      if (typed_count < sizeof(typed_buffer) - 1) {
        typed_buffer[typed_count++] = ch;
        terminal_write_char(ch);
      }
      break;
    }
  }
}
