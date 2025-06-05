#include "terminal.h"

size_t cursor_pos_x = 0; // Column
size_t cursor_pos_y = 0; // Row
uint8_t font_color;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;

static inline uint8_t vga_entry_color(VgaColor foreground,
                                      VgaColor background) {
  return foreground | background << 4;
}

static inline uint16_t vga_entry(uint8_t entry, uint8_t color) {
  return (uint16_t)entry | (uint16_t)color << 8;
}

static inline size_t cursor_get_index() {
  return cursor_pos_y * VGA_WIDTH + cursor_pos_x;
}

void terminal_initialize(void) {
  font_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal_clear();
  terminal_enable_cursor(13, 15);
  terminal_cursor_update_position();
}

void terminal_clear() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', font_color);
    }
  }
  cursor_pos_x = 0;
  cursor_pos_y = 0;
  terminal_cursor_update_position();
}

void terminal_set_color(VgaColor foreground, VgaColor background) {
  font_color = vga_entry_color(foreground, background);
}

void terminal_scroll() {
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      terminal_buffer[(y - 1) * VGA_WIDTH + x] =
          terminal_buffer[y * VGA_WIDTH + x];
    }
  }

  for (size_t x = 0; x < VGA_WIDTH; x++) {
    terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
        vga_entry(' ', font_color);
  }

  cursor_pos_y = VGA_HEIGHT - 1;
  cursor_pos_x = 0;
  terminal_cursor_update_position();
}

void terminal_write_char(const char data) {
  switch (data) {
  case '\n':
    cursor_pos_x = 0;
    cursor_pos_y++;
    if (cursor_pos_y == VGA_HEIGHT) {
      terminal_scroll();
    }
    terminal_cursor_update_position();
    return;

  case '\t':
    terminal_write_string("    ");
    return;

  case '\b':
    if (cursor_pos_x > 0) {
      cursor_pos_x--;
    } else if (cursor_pos_y > 0) {
      cursor_pos_y--;
      cursor_pos_x = VGA_WIDTH - 1;
    } else {
      return;
    }
    terminal_buffer[cursor_get_index()] = vga_entry(' ', font_color);
    terminal_cursor_update_position();
    return;

  default:
    break;
  }

  terminal_buffer[cursor_get_index()] = vga_entry(data, font_color);
  cursor_pos_x++;

  if (cursor_pos_x == VGA_WIDTH) {
    cursor_pos_x = 0;
    cursor_pos_y++;
    if (cursor_pos_y == VGA_HEIGHT) {
      terminal_scroll();
    }
  }

  terminal_cursor_update_position();
}

void terminal_write_string(const char *data) {
  while (*data) {
    if (data[0] == '@' && data[1] == '[' && data[3] == ']') {
      switch (data[2]) {
      case 'R':
        terminal_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        break;
      case 'G':
        terminal_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        break;
      case 'B':
        terminal_set_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
        break;
      case 'C':
        terminal_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
        break;
      case 'M':
        terminal_set_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
        break;
      case '!':
        terminal_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        break;
      default:
        terminal_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        break;
      }
      data += 4;
      continue;
    }

    // Экранирование "@[" → просто вывод
    if (data[0] == '@' && data[1] == '[') {
      terminal_write_char('@');
      data++;
      continue;
    }

    terminal_write_char(*data);
    data++;
  }
}

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
  outb(0x3D4, 0x0A);
  outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

  outb(0x3D4, 0x0B);
  outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void terminal_disable_cursor() {
  outb(0x3D4, 0x0A);
  outb(0x3D5, 0x20);
}

void terminal_cursor_set_position(uint16_t x, uint16_t y) {
  cursor_pos_x = x;
  cursor_pos_y = y;
  uint16_t pos = y * VGA_WIDTH + x;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_cursor_update_position() {
  terminal_cursor_set_position(cursor_pos_x, cursor_pos_y);
}

uint16_t terminal_cursor_get_position() {
  uint16_t pos = 0;
  outb(0x3D4, 0x0F);
  pos |= inb(0x3D5);
  outb(0x3D4, 0x0E);
  pos |= ((uint16_t)inb(0x3D5)) << 8;
  return pos;
}
