/* INFO: TOPOS PS2 KEYBOARD DRIVER
 * PS2 CAN BE EMULATED BY BIOS IF YOU ARE USING USB
 * WORKS ONLY ON BIOS OR UIFI WITH CSM/LEGACY SUPPORT
 */

#pragma once
#include "../cpu/idt.h"
#include "../cpu/ports.h"
#include <stdbool.h>
#include <stdint.h>

#define KB_KEY_INVALID 0x00
#define KB_KEY_ESC 0x01
#define KB_KEY_1 0x02
#define KB_KEY_2 0x03
#define KB_KEY_3 0x04
#define KB_KEY_4 0x05
#define KB_KEY_5 0x06
#define KB_KEY_6 0x07
#define KB_KEY_7 0x08
#define KB_KEY_8 0x09
#define KB_KEY_9 0x0A
#define KB_KEY_0 0x0B
#define KB_KEY_MINUS 0x0C
#define KB_KEY_EQUAL 0x0D
#define KB_KEY_BACKSPACE 0x0E
#define KB_KEY_TAB 0x0F
#define KB_KEY_Q 0x10
#define KB_KEY_W 0x11
#define KB_KEY_E 0x12
#define KB_KEY_R 0x13
#define KB_KEY_T 0x14
#define KB_KEY_Y 0x15
#define KB_KEY_U 0x16
#define KB_KEY_I 0x17
#define KB_KEY_O 0x18
#define KB_KEY_P 0x19
#define KB_KEY_LSQUARE_BRACKET 0x1A
#define KB_KEY_RSQUARE_BRACKET 0x1B
#define KB_KEY_ENTER 0x1C
#define KB_KEY_LCTRL 0x1D
#define KB_KEY_A 0x1E
#define KB_KEY_S 0x1F
#define KB_KEY_D 0x20
#define KB_KEY_F 0x21
#define KB_KEY_G 0x22
#define KB_KEY_H 0x23
#define KB_KEY_J 0x24
#define KB_KEY_K 0x25
#define KB_KEY_L 0x26
#define KB_KEY_SEMICOLON 0x27
#define KB_KEY_SINGLE_QUOTE 0x28
#define KB_KEY_BACKTICK 0x29
#define KB_KEY_LSHIFT 0x2A
#define KB_KEY_BACKSLASH 0x2B
#define KB_KEY_Z 0x2C
#define KB_KEY_X 0x2D
#define KB_KEY_C 0x2E
#define KB_KEY_V 0x2F
#define KB_KEY_B 0x30
#define KB_KEY_N 0x31
#define KB_KEY_M 0x32
#define KB_KEY_COMMA 0x33
#define KB_KEY_FULLSTOP 0x34
#define KB_KEY_SLASH 0x35
#define KB_KEY_RSHIFT 0x36
#define KB_KEYPAD_ASTERIKS 0x37
#define KB_KEY_LALT 0x38
#define KB_KEY_SPACE 0x39
#define KB_KEY_CAPSLOCK 0x3A
#define KB_KEY_F1 0x3B
#define KB_KEY_F2 0x3C
#define KB_KEY_F3 0x3D
#define KB_KEY_F4 0x3E
#define KB_KEY_F5 0x3F
#define KB_KEY_F6 0x40
#define KB_KEY_F7 0x41
#define KB_KEY_F8 0x42
#define KB_KEY_F9 0x43
#define KB_KEY_F10 0x44
#define KB_KEY_NUMLOCK 0x45
#define KB_KEY_SCROLL_LOCK 0x46
#define KB_KEYPAD_7 0x47
#define KB_KEYPAD_8 0x48
#define KB_KEYPAD_9 0x49
#define KB_KEYPAD_MINUS 0x4A
#define KB_KEYPAD_4 0x4B
#define KB_KEYPAD_5 0x4C
#define KB_KEYPAD_6 0x4D
#define KB_KEYPAD_PLUS 0x4E
#define KB_KEYPAD_1 0x4F
#define KB_KEYPAD_2 0x50
#define KB_KEYPAD_3 0x51
#define KB_KEYPAD_0 0x52
#define KB_KEYPAD_FULLSTOP 0x53
// + 4
#define KB_KEY_F11 0x57
#define KB_KEY_F12 0x58
// + E0..
#define KB_KEYPAD_ENTER 0xE01C
#define KB_KEY_RCTRL 0xE01D
#define KB_KEYPAD_SLASH 0xE035
#define KB_KEY_RALT 0xE038
#define KB_KEY_HOME 0xE047
#define KB_KEY_CURSOR_UP 0xE048
#define KB_KEY_PAGE_UP 0xE049
#define KB_KEY_CURSOR_LEFT 0xE04B
#define KB_KEY_CURSOR_RIGHT 0xE04D
#define KB_KEY_END 0xE04F
#define KB_KEY_CURSOR_DOWN 0xE050
#define KB_KEY_PAGE_DOWN 0xE051
#define KB_KEY_INSERT 0xE052
#define KB_KEY_DELETE 0xE053
#define KB_KEY_LSUPER 0xE05B
#define KB_KEY_RSUPER 0xE05C
#define KB_KEY_APPS 0xE05D
#define KB_KEY_POWER 0xE05E
#define KB_KEY_SLEEP 0xE05F
#define KB_KEY_WAKE 0xE063

#define GAG_CHAR -1

#define KEYBOARD_BUFFER_SIZE 256

typedef struct {
  uint32_t scancode;
  bool pressed;
} KeyboardKey;

/// Must do it before using keyboard.
void keyboard_initialize();
/// Waiting until any key pressed and then return it.
KeyboardKey keyboard_read_key();
/// Return last pressed key.
KeyboardKey keyboard_get_key();
/// Return associated char for keyboard key ONLY IF KEY PRESSED.
/// You MUST check if char isn't a GAG_CHAR before cast/using it.
/// Proper cast: (char)(unsigned char) from int
int keyboard_key_to_ascii(KeyboardKey key, bool uppercase);
/// Return associated char for keyboard key scancode.
/// You MUST check if char isn't a GAG_CHAR before cast/using it.
/// Proper cast: (char)(unsigned char) from int
int keyboard_key_scancode_to_ascii(uint32_t scancode, bool uppercase);
/// Function associated with keyboard interrupts, DONT USE IT.
void keyboard_handler(InterruptRegisters *regs);
/// Keyboard state function
bool keyboard_shift_pressed();
