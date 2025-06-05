/* INFO: TOPOS PS2 KEYBOARD DRIVER
 * PS2 CAN BE EMULATED BY BIOS IF YOU ARE USING USB
 * WORKS ONLY ON BIOS OR UIFI WITH CSM/LEGACY SUPPORT
 */

#include "keyboard.h"

const char KB_LOWERCASE_PRINTABLE[] = {
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

const char KB_UPPERCASE_PRINTABLE[] = {
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

bool e0 = false;

// Keyboard state
bool lshift_pressed = false;
bool rshift_pressed = false;

KeyboardKey keyboard_buffer[KEYBOARD_BUFFER_SIZE];
int buffer_head = 0;
int buffer_tail = 0;

bool buffer_empty() { return buffer_head == buffer_tail; }

bool buffer_full() {
  return ((buffer_head + 1) % KEYBOARD_BUFFER_SIZE) == buffer_tail;
}

void buffer_push(KeyboardKey key) {
  if (!buffer_full()) {
    keyboard_buffer[buffer_head] = key;
    buffer_head = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;
  }
}

KeyboardKey buffer_pop() {
  KeyboardKey key = {0, false};
  if (!buffer_empty()) {
    key = keyboard_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
  }
  return key;
}

void keyboard_initialize() { irq_install_handler(1, &keyboard_handler); }

KeyboardKey keyboard_read_key() {
  while (buffer_empty())
    asm("hlt");
  return buffer_pop();
}

int keyboard_key_to_ascii(KeyboardKey key, bool uppercase) {
  if (key.pressed) {
    return keyboard_key_scancode_to_ascii(key.scancode, uppercase);
  } else {
    return GAG_CHAR;
  }
}

int keyboard_key_scancode_to_ascii(uint32_t scancode, bool uppercase) {
  uint32_t printable = scancode;

  // Ignoring special keys
  switch (scancode) {
  case KB_KEY_CURSOR_UP:
    return GAG_CHAR;
  case KB_KEY_CURSOR_DOWN:
    return GAG_CHAR;
  case KB_KEY_CURSOR_LEFT:
    return GAG_CHAR;
  case KB_KEY_CURSOR_RIGHT:
    return GAG_CHAR;
  case KB_KEY_HOME:
    return GAG_CHAR;
  case KB_KEY_PAGE_UP:
    return GAG_CHAR;
  case KB_KEY_PAGE_DOWN:
    return GAG_CHAR;
  case KB_KEY_END:
    return GAG_CHAR;
  }

  if (scancode > 0xE000)
    printable -= 0xE000;
  if (printable < KB_KEYPAD_FULLSTOP) {
    if (uppercase)
      return KB_UPPERCASE_PRINTABLE[printable];
    else
      return KB_LOWERCASE_PRINTABLE[printable];
  } else if (scancode == KB_KEY_DELETE) {
    return '\177';
  } else {
    return GAG_CHAR;
  }
}

void keyboard_handler(InterruptRegisters *regs) {
  (void)regs;

  uint8_t keycode = inb(0x60);
  if (keycode == 0xE0) {
    e0 = true;
    return;
  }

  bool pressed = !(keycode & 0x80);
  uint16_t scancode = e0 ? (0xE000 | (keycode & 0x7F)) : (keycode & 0x7F);

  if (scancode == KB_KEY_LSHIFT)
    lshift_pressed = pressed;
  else if (scancode == KB_KEY_RSHIFT)
    rshift_pressed = pressed;

  buffer_push((KeyboardKey){scancode, pressed});

  e0 = false;
}

bool keyboard_shift_pressed() { return (lshift_pressed || rshift_pressed); }
