#include "terminal.h"
#include <stddef.h>
#include <stdint.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;

static inline uint8_t vga_entry_color(enum vga_color foreground,
                                      enum vga_color background) {
  return foreground | background << 4;
}

static inline uint16_t vga_entry(uint8_t entry, uint8_t color) {
  return (uint16_t)entry | (uint16_t)color << 8;
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal_clear();
}

void terminal_clear() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_set_color(enum vga_color foreground, enum vga_color background) {
  terminal_color = vga_entry_color(foreground, background);
}

void terminal_write_char(const char data) {
  if (data == '\n') {
    terminal_row++;
    terminal_column = 0;
    return;
  }

  const size_t index = terminal_row * VGA_WIDTH + terminal_column;
  terminal_buffer[index] = vga_entry(data, terminal_color);
  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminal_row = 0;
    }
  }
}

void terminal_write_string(const char *data) {
  while (*data) {
    terminal_write_char(*data);
    data++;
  }
}
