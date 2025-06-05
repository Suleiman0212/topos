#include "../drivers/keyboard.h"
#include "../drivers/terminal.h"
#include "../std/str.h"
#include <stdbool.h>
#include <stdint.h>

// clang-format off
static const char* TOPOS_LOGO =
"$$$$$$$$\\                   $$$$$$\\   $$$$$$\\  \n"
"\\__$$  __|                 $$  __$$\\ $$  __$$\\ \n"
"   $$ | $$$$$$\\   $$$$$$\\  $$ /  $$ |$$ /  \\__|\n"
"   $$ |$$  __$$\\ $$  __$$\\ $$ |  $$ |\\$$$$$$\\  \n"
"   $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ | \\____$$\\ \n"
"   $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$\\   $$ |\n"
"   $$ |\\$$$$$$  |$$$$$$$  | $$$$$$  |\\$$$$$$  |\n"
"   \\__| \\______/ $$  ____/  \\______/  \\______/                      @[R]v0.0.1 ALPHA@[!]"
"                 $$ |                         \n"
"                 $$ |                         \n"
"                 \\__|                         \n";
// clang-format on

#define BUFFER_SIZE 128

void shell_run();
