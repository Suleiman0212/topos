/* INFO: TOPOS PS2 KEYBOARD DRIVER
 * PS2 CAN BE EMULATED BY BIOS IF YOU ARE USING USB
 * WORKS ONLY ON BIOS OR UIFI WITH CSM/LEGACY SUPPORT
 * WRITTEN BY KIRIMOV SULEIMAN
 */

#pragma once

#include "../cpu/idt.h"
#include <stdbool.h>

/* TODO: We are currently doesn't support multimedia keys
 * but maybe someday we'll add them.
 */
typedef enum {
  KB_PHYS_KEY_INVALID = 0x00,
  KB_PHYS_KEY_ESC = 0x01,
  KB_PHYS_KEY_1 = 0x02,
  KB_PHYS_KEY_2 = 0x03,
  KB_PHYS_KEY_3 = 0x04,
  KB_PHYS_KEY_4 = 0x05,
  KB_PHYS_KEY_5 = 0x06,
  KB_PHYS_KEY_6 = 0x07,
  KB_PHYS_KEY_7 = 0x08,
  KB_PHYS_KEY_8 = 0x09,
  KB_PHYS_KEY_9 = 0x0A,
  KB_PHYS_KEY_0 = 0x0B,
  KB_PHYS_KEY_MINUS = 0x0C,
  KB_PHYS_KEY_EQUAL = 0x0D,
  KB_PHYS_KEY_BACKSPACE = 0x0E,
  KB_PHYS_KEY_TAB = 0x0F,
  KB_PHYS_KEY_Q = 0x10,
  KB_PHYS_KEY_W = 0x11,
  KB_PHYS_KEY_E = 0x12,
  KB_PHYS_KEY_R = 0x13,
  KB_PHYS_KEY_T = 0x14,
  KB_PHYS_KEY_Y = 0x15,
  KB_PHYS_KEY_U = 0x16,
  KB_PHYS_KEY_I = 0x17,
  KB_PHYS_KEY_O = 0x18,
  KB_PHYS_KEY_P = 0x19,
  KB_PHYS_KEY_LSQUARE_BRACKET = 0x1A,
  KB_PHYS_KEY_RSQUARE_BRACKET = 0x1B,
  KB_PHYS_KEY_ENTER = 0x1C,
  KB_PHYS_KEY_LCTRL = 0x1D,
  KB_PHYS_KEY_A = 0x1E,
  KB_PHYS_KEY_S = 0x1F,
  KB_PHYS_KEY_D = 0x20,
  KB_PHYS_KEY_F = 0x21,
  KB_PHYS_KEY_G = 0x22,
  KB_PHYS_KEY_H = 0x23,
  KB_PHYS_KEY_J = 0x24,
  KB_PHYS_KEY_K = 0x25,
  KB_PHYS_KEY_L = 0x26,
  KB_PHYS_KEY_SEMICOLON = 0x27,
  KB_PHYS_KEY_SINGLE_QUOTE = 0x28,
  KB_PHYS_KEY_BACK_TICK = 0x29,
  KB_PHYS_KEY_LSHIFT = 0x2A,
  KB_PHYS_KEY_BACK_SLASH = 0x2B,
  KB_PHYS_KEY_Z = 0x2C,
  KB_PHYS_KEY_X = 0x2D,
  KB_PHYS_KEY_C = 0x2E,
  KB_PHYS_KEY_V = 0x2F,
  KB_PHYS_KEY_B = 0x30,
  KB_PHYS_KEY_N = 0x31,
  KB_PHYS_KEY_M = 0x32,
  KB_PHYS_KEY_COMMA = 0x33,
  KB_PHYS_KEY_FULLSTOP = 0x34,
  KB_PHYS_KEY_SLASH = 0x35,
  KB_PHYS_KEY_RSHIFT = 0x36,
  KB_PHYS_KEYPAD_ASTERIKS = 0x37,
  KB_PHYS_KEY_LALT = 0x38,
  KB_PHYS_KEY_SPACE = 0x39,
  KB_PHYS_KEY_CAPS_LOCK = 0x3A,
  KB_PHYS_KEY_F1 = 0x3B,
  KB_PHYS_KEY_F2 = 0x3C,
  KB_PHYS_KEY_F3 = 0x3D,
  KB_PHYS_KEY_F4 = 0x3E,
  KB_PHYS_KEY_F5 = 0x3F,
  KB_PHYS_KEY_F6 = 0x40,
  KB_PHYS_KEY_F7 = 0x41,
  KB_PHYS_KEY_F8 = 0x42,
  KB_PHYS_KEY_F9 = 0x43,
  KB_PHYS_KEY_F10 = 0x44,
  KB_PHYS_KEY_NUMBER_LOCK = 0x45,
  KB_PHYS_KEY_SCROLL_LOCK = 0x46,
  KB_PHYS_KEYPAD_7 = 0x47,
  KB_PHYS_KEYPAD_8 = 0x48,
  KB_PHYS_KEYPAD_9 = 0x49,
  KB_PHYS_KEYPAD_MINUS = 0x4A,
  KB_PHYS_KEYPAD_4 = 0x4B,
  KB_PHYS_KEYPAD_5 = 0x4C,
  KB_PHYS_KEYPAD_6 = 0x4D,
  KB_PHYS_KEYPAD_PLUS = 0x4E,
  KB_PHYS_KEYPAD_1 = 0x4F,
  KB_PHYS_KEYPAD_2 = 0x50,
  KB_PHYS_KEYPAD_3 = 0x51,
  KB_PHYS_KEYPAD_0 = 0x52,
  KB_PHYS_KEYPAD_FULLSTOP = 0x53,
  KB_PHYS_KEY_F11 = 0x57,
  KB_PHYS_KEY_F12 = 0x58,
  KB_PHYS_KEYPAD_ENTER = 0xE01C,
  KB_PHYS_KEY_RCTRL = 0xE01D,
  KB_PHYS_KEYPAD_SLASH = 0xE035,
  KB_PHYS_KEY_RALT = 0xE038,
  KB_PHYS_KEY_HOME = 0xE047,
  KB_PHYS_KEY_CURSOR_UP = 0xE048,
  KB_PHYS_KEY_PAGE_UP = 0xE049,
  KB_PHYS_KEY_CURSOR_LEFT = 0xE04B,
  KB_PHYS_KEY_CURSOR_RIGHT = 0xE04D,
  KB_PHYS_KEY_END = 0xE04F,
  KB_PHYS_KEY_CURSOR_DOWN = 0xE050,
  KB_PHYS_KEY_PAGE_DOWN = 0xE051,
  KB_PHYS_KEY_INSERT = 0xE052,
  KB_PHYS_KEY_DELETE = 0xE053,
  KB_PHYS_KEY_LSUPER = 0xE05B,
  KB_PHYS_KEY_RSUPER = 0xE05C,
  KB_PHYS_KEY_APPS = 0xE05D,
  KB_PHYS_ACPI_POWER = 0xE05E,
  KB_PHYS_ACPI_SLEEP = 0xE05F,
  KB_PHYS_ACPI_WAKE = 0xE063,
} KbPhysicalKey;

#define GAG_CHAR -1
static const char LOWERCASE_KB[] = {
    GAG_CHAR, GAG_CHAR, '1',      '2',      '3',      '4',      '5',
    '6',      '7',      '8',      '9',      '0',      '-',      '=',
    '\b',     '\t',     'q',      'w',      'e',      'r',      't',
    'y',      'u',      'i',      'o',      'p',      '[',      ']',
    '\n',     GAG_CHAR, 'a',      's',      'd',      'f',      'g',
    'h',      'j',      'k',      'l',      ';',      '\'',     '`',
    GAG_CHAR, '\\',     'z',      'x',      'c',      'v',      'b',
    'n',      'm',      ',',      '.',      '/',      GAG_CHAR, '*',
    GAG_CHAR, ' ',      GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR,
    GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR,
    GAG_CHAR, '7',      '8',      '9',      '-',      '4',      '5',
    '6',      '+',      '1',      '2',      '3',      '0',      '.', // End 0x53
};

static const char UPPERCASE_KB[] = {
    GAG_CHAR, GAG_CHAR, '!',      '@',      '#',      '$',      '%',
    '^',      '&',      '*',      '(',      ')',      '_',      '+',
    '\b',     '\t',     'Q',      'W',      'E',      'R',      'T',
    'Y',      'U',      'I',      'O',      'P',      '{',      '}',
    '\n',     GAG_CHAR, 'A',      'S',      'D',      'F',      'G',
    'H',      'J',      'K',      'L',      ':',      '"',      '~',
    GAG_CHAR, '|',      'Z',      'X',      'C',      'V',      'B',
    'N',      'M',      '<',      '>',      '?',      GAG_CHAR, '*',
    GAG_CHAR, ' ',      GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR,
    GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR, GAG_CHAR,
    GAG_CHAR, '7',      '8',      '9',      '-',      '4',      '5',
    '6',      '+',      '1',      '2',      '3',      '0',      '.', // End 0x53
};

void keboard_initialize();
KbPhysicalKey keyboard_read_phys_key();
char keyboard_read_char();
int keyboard_phys_key_to_char(KbPhysicalKey key, bool uppercase);
bool keyboard_shift_pressed(KbPhysicalKey key);
void keyboard_handler(InterruptRegisters *regs);
