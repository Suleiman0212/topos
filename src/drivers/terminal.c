#include "terminal.h"
#include "../cpu/ports.h"
#include <stddef.h>
#include <stdint.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;

static inline uint8_t vga_entry_color(VgaColor foreground,
                                      VgaColor background) {
  return foreground | background << 4;
}

static inline uint16_t vga_entry(uint8_t entry, uint8_t color) {
  return (uint16_t)entry | (uint16_t)color << 8;
}

static inline size_t terminal_get_index() {
  return terminal_row * VGA_WIDTH + terminal_column;
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal_clear();
  terminal_enable_cursor(13, 15);
  terminal_cursor_set_position(0, 0);
}

void terminal_clear() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      terminal_buffer[terminal_get_index()] = vga_entry(' ', terminal_color);
      terminal_cursor_set_position(0, 0);
    }
  }
}

void terminal_set_color(VgaColor foreground, VgaColor background) {
  terminal_color = vga_entry_color(foreground, background);
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
        vga_entry(' ', terminal_color);
  }

  terminal_row = VGA_HEIGHT - 1;
  terminal_cursor_set_position(0, 0);
}

void terminal_write_char(const char data) {
  if (data == '\n') {
    terminal_row++;
    terminal_column = 0;
    if (terminal_row == VGA_HEIGHT) {
      terminal_scroll();
    }
    terminal_cursor_update_position();
    return;
  } else if (data == '\t') {
    terminal_write_string("    ");
  } else if (data == '\b') {
    if (terminal_column > 0) {
      terminal_column--;
    } else if (terminal_row > 0) {
      terminal_row--;
      terminal_column = VGA_WIDTH - 1;
    } else {
      return;
    }
    terminal_buffer[terminal_get_index()] = vga_entry(' ', terminal_color);
    terminal_cursor_update_position();
    return;
  } else if (data == '\f') {
    terminal_clear();
    terminal_row = 0;
    terminal_column = 0;
    terminal_cursor_update_position();
    return;
  }

  terminal_buffer[terminal_get_index()] = vga_entry(data, terminal_color);

  terminal_column++;
  terminal_cursor_update_position();
  if (terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    terminal_row++;
    terminal_cursor_update_position();
    if (terminal_row == VGA_HEIGHT) {
      terminal_scroll();
    }
  }
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
  uint16_t pos = y * VGA_WIDTH + x;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_cursor_update_position() {
  terminal_cursor_set_position(terminal_column, terminal_row);
}

uint16_t terminal_cursor_get_position() {
  uint16_t pos = 0;
  outb(0x3D4, 0x0F);
  pos |= inb(0x3D5);
  outb(0x3D4, 0x0E);
  pos |= ((uint16_t)inb(0x3D5)) << 8;
  return pos;
}
