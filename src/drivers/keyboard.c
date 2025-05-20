/* INFO: TOPOS PS2 KEYBOARD DRIVER
 * PS2 CAN BE EMULATED BY BIOS IF YOU ARE USING USB
 * WORKS ONLY ON BIOS OR UIFI WITH CSM/LEGACY SUPPORT
 * WRITTEN BY KIRIMOV SULEIMAN 5.19.2025
 * LAST UPDATE 5.18.2025
 */

#include "keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/ports.h"
#include <stdbool.h>

KbPhysicalKey keyboard_scancode_to_phys_key(uint16_t code) {
  switch (code) {
  case 0x01:
    return KB_PHYS_KEY_ESC;
  case 0x02:
    return KB_PHYS_KEY_1;
  case 0x03:
    return KB_PHYS_KEY_2;
  case 0x04:
    return KB_PHYS_KEY_3;
  case 0x05:
    return KB_PHYS_KEY_4;
  case 0x06:
    return KB_PHYS_KEY_5;
  case 0x07:
    return KB_PHYS_KEY_6;
  case 0x08:
    return KB_PHYS_KEY_7;
  case 0x09:
    return KB_PHYS_KEY_8;
  case 0x0A:
    return KB_PHYS_KEY_9;
  case 0x0B:
    return KB_PHYS_KEY_0;
  case 0x0C:
    return KB_PHYS_KEY_MINUS;
  case 0x0D:
    return KB_PHYS_KEY_EQUAL;
  case 0x0E:
    return KB_PHYS_KEY_BACKSPACE;
  case 0x0F:
    return KB_PHYS_KEY_TAB;
  case 0x10:
    return KB_PHYS_KEY_Q;
  case 0x11:
    return KB_PHYS_KEY_W;
  case 0x12:
    return KB_PHYS_KEY_E;
  case 0x13:
    return KB_PHYS_KEY_R;
  case 0x14:
    return KB_PHYS_KEY_T;
  case 0x15:
    return KB_PHYS_KEY_Y;
  case 0x16:
    return KB_PHYS_KEY_U;
  case 0x17:
    return KB_PHYS_KEY_I;
  case 0x18:
    return KB_PHYS_KEY_O;
  case 0x19:
    return KB_PHYS_KEY_P;
  case 0x1A:
    return KB_PHYS_KEY_LSQUARE_BRACKET;
  case 0x1B:
    return KB_PHYS_KEY_RSQUARE_BRACKET;
  case 0x1C:
    return KB_PHYS_KEY_ENTER;
  case 0x1D:
    return KB_PHYS_KEY_LCTRL;
  case 0x1E:
    return KB_PHYS_KEY_A;
  case 0x1F:
    return KB_PHYS_KEY_S;
  case 0x20:
    return KB_PHYS_KEY_D;
  case 0x21:
    return KB_PHYS_KEY_F;
  case 0x22:
    return KB_PHYS_KEY_G;
  case 0x23:
    return KB_PHYS_KEY_H;
  case 0x24:
    return KB_PHYS_KEY_J;
  case 0x25:
    return KB_PHYS_KEY_K;
  case 0x26:
    return KB_PHYS_KEY_L;
  case 0x27:
    return KB_PHYS_KEY_SEMICOLON;
  case 0x28:
    return KB_PHYS_KEY_SINGLE_QUOTE;
  case 0x29:
    return KB_PHYS_KEY_BACK_TICK;
  case 0x2A:
    return KB_PHYS_KEY_LSHIFT;
  case 0x2B:
    return KB_PHYS_KEY_BACK_SLASH;
  case 0x2C:
    return KB_PHYS_KEY_Z;
  case 0x2D:
    return KB_PHYS_KEY_X;
  case 0x2E:
    return KB_PHYS_KEY_C;
  case 0x2F:
    return KB_PHYS_KEY_V;
  case 0x30:
    return KB_PHYS_KEY_B;
  case 0x31:
    return KB_PHYS_KEY_N;
  case 0x32:
    return KB_PHYS_KEY_M;
  case 0x33:
    return KB_PHYS_KEY_COMMA;
  case 0x34:
    return KB_PHYS_KEY_FULLSTOP;
  case 0x35:
    return KB_PHYS_KEY_SLASH;
  case 0x36:
    return KB_PHYS_KEY_RSHIFT;
  case 0x37:
    return KB_PHYS_KEYPAD_ASTERIKS;
  case 0x38:
    return KB_PHYS_KEY_LALT;
  case 0x39:
    return KB_PHYS_KEY_SPACE;
  case 0x3A:
    return KB_PHYS_KEY_CAPS_LOCK;
  case 0x3B:
    return KB_PHYS_KEY_F1;
  case 0x3C:
    return KB_PHYS_KEY_F2;
  case 0x3D:
    return KB_PHYS_KEY_F3;
  case 0x3E:
    return KB_PHYS_KEY_F4;
  case 0x3F:
    return KB_PHYS_KEY_F5;
  case 0x40:
    return KB_PHYS_KEY_F6;
  case 0x41:
    return KB_PHYS_KEY_F7;
  case 0x42:
    return KB_PHYS_KEY_F8;
  case 0x43:
    return KB_PHYS_KEY_F9;
  case 0x44:
    return KB_PHYS_KEY_F10;
  case 0x45:
    return KB_PHYS_KEY_NUMBER_LOCK;
  case 0x46:
    return KB_PHYS_KEY_SCROLL_LOCK;
  case 0x47:
    return KB_PHYS_KEYPAD_7;
  case 0x48:
    return KB_PHYS_KEYPAD_8;
  case 0x49:
    return KB_PHYS_KEYPAD_9;
  case 0x4A:
    return KB_PHYS_KEYPAD_MINUS;
  case 0x4B:
    return KB_PHYS_KEYPAD_4;
  case 0x4C:
    return KB_PHYS_KEYPAD_5;
  case 0x4D:
    return KB_PHYS_KEYPAD_6;
  case 0x4E:
    return KB_PHYS_KEYPAD_PLUS;
  case 0x4F:
    return KB_PHYS_KEYPAD_1;
  case 0x50:
    return KB_PHYS_KEYPAD_2;
  case 0x51:
    return KB_PHYS_KEYPAD_3;
  case 0x52:
    return KB_PHYS_KEYPAD_0;
  case 0x53:
    return KB_PHYS_KEYPAD_FULLSTOP;
  case 0x57:
    return KB_PHYS_KEY_F11;
  case 0x58:
    return KB_PHYS_KEY_F12;
  case 0xE01C:
    return KB_PHYS_KEY_ENTER;
  case 0xE01D:
    return KB_PHYS_KEY_RCTRL;
  case 0xE035:
    return KB_PHYS_KEYPAD_SLASH;
  case 0xE038:
    return KB_PHYS_KEY_RALT;
  case 0xE047:
    return KB_PHYS_KEY_HOME;
  case 0xE048:
    return KB_PHYS_KEY_CURSOR_UP;
  case 0xE049:
    return KB_PHYS_KEY_PAGE_UP;
  case 0xE04B:
    return KB_PHYS_KEY_CURSOR_LEFT;
  case 0xE04D:
    return KB_PHYS_KEY_CURSOR_RIGHT;
  case 0xE04F:
    return KB_PHYS_KEY_END;
  case 0xE050:
    return KB_PHYS_KEY_CURSOR_DOWN;
  case 0xE051:
    return KB_PHYS_KEY_PAGE_DOWN;
  case 0xE052:
    return KB_PHYS_KEY_INSERT;
  case 0xE053:
    return KB_PHYS_KEY_DELETE;
  case 0xE05B:
    return KB_PHYS_KEY_LSUPER;
  case 0xE05C:
    return KB_PHYS_KEY_RSUPER;
  case 0xE05D:
    return KB_PHYS_KEY_APPS;
  case 0xE05E:
    return KB_PHYS_ACPI_POWER;
  case 0xE05F:
    return KB_PHYS_ACPI_SLEEP;
  case 0xE063:
    return KB_PHYS_ACPI_WAKE;
  default:
    return KB_PHYS_KEY_INVALID;
  }
}

bool read_request = false;
KbPhysicalKey key_buffer;
bool key_buffer_press;
bool e0 = false;
bool lshift = false;
bool rshift = false;
bool capslock = false;
bool numlock = false;
bool scroll_lock = false;
bool lctr = false;
bool rctrl = false;
bool lalt = false;
bool ralt = false;
bool lsuper = false;
bool rsuper = false;

void keboard_initialize() { irq_install_handler(1, &keyboard_handler); }

KbPhysicalKey keyboard_read_phys_key() {
  read_request = true;
  while (true) {
    if (read_request) {
      __asm__ __volatile__("hlt");
    } else {
      break;
    }
  }
  return key_buffer;
}

/// Waiting for valid char and then return it.
/// List of chars you can see on src/drivers/keyboard.h
char keyboard_read_char() {
  while (true) {
    KbPhysicalKey key = keyboard_read_phys_key();
    int ch = keyboard_phys_key_to_char(key, keyboard_shift_pressed(key));
    if (ch == GAG_CHAR) {
      continue;
    }
    return (char)(unsigned char)ch;
  }
}

/// Returning int value of char.
/// List of chars you can see on src/drivers/keyboard.h.
/// You MUST check if char != GAG_CHAR and then cast to char.
/// Like this:
/// if (ch != GAG_CHAR)
///      (char)(unsigned char)ch;
int keyboard_phys_key_to_char(KbPhysicalKey key, bool uppercase) {
  if (key < KB_PHYS_KEYPAD_FULLSTOP) {
    if (uppercase)
      return UPPERCASE_KB[key];
    else
      return LOWERCASE_KB[key];
  } else if (key == KB_PHYS_KEY_DELETE) {
    return '\177';
  } else {
    return GAG_CHAR;
  }
}

bool is_alpha_key(KbPhysicalKey key) {
  return (key >= KB_PHYS_KEY_A && key <= KB_PHYS_KEY_Z);
}

bool keyboard_shift_pressed(KbPhysicalKey key) {
  if (is_alpha_key(key)) {
    return lshift || rshift ? !capslock : capslock;
  } else {
    return lshift || rshift;
  }
}

void keyboard_handler(InterruptRegisters *regs) {
  (void)regs;

  uint8_t code = inb(0x60);

  if (code == 0xE0) {
    e0 = true;
    return;
  }

  bool press = !(code & 0x80);
  uint8_t scan_code = code & 0x7F;
  uint16_t full_code = e0 ? (0xE000 | scan_code) : scan_code;

  key_buffer = keyboard_scancode_to_phys_key(full_code);

  if (!press) {
    if (key_buffer == KB_PHYS_KEY_LSHIFT) {
      lshift = false;
    } else if (key_buffer == KB_PHYS_KEY_RSHIFT) {
      rshift = false;
    }

    e0 = false;
    return;
  }

  if (key_buffer == KB_PHYS_KEY_LSHIFT) {
    lshift = true;
  } else if (key_buffer == KB_PHYS_KEY_RSHIFT) {
    rshift = true;
  } else if (key_buffer == KB_PHYS_KEY_CAPS_LOCK) {
    capslock = !capslock;
  } else if (key_buffer == KB_PHYS_KEY_NUMBER_LOCK) {
    numlock = !numlock;
  } else if (key_buffer == KB_PHYS_KEY_SCROLL_LOCK) {
    scroll_lock = !scroll_lock;
  } else if (key_buffer == KB_PHYS_KEY_LCTRL ||
             key_buffer == KB_PHYS_KEY_RCTRL ||
             key_buffer == KB_PHYS_KEY_LSUPER ||
             key_buffer == KB_PHYS_KEY_RSUPER ||
             key_buffer == KB_PHYS_KEY_LALT || key_buffer == KB_PHYS_KEY_RALT ||
             key_buffer == KB_PHYS_KEY_CURSOR_UP ||
             key_buffer == KB_PHYS_KEY_CURSOR_DOWN ||
             key_buffer == KB_PHYS_KEY_CURSOR_LEFT ||
             key_buffer == KB_PHYS_KEY_CURSOR_RIGHT) {
  } else {
    key_buffer_press = true;
    read_request = false;
  }

  e0 = false;
}
