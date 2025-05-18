#include "timer.h"
#include "../cpu/pit.h"

uint64_t start_ticks = 0;
uint64_t stop_ticks = 0;

void timer_start() { start_ticks = pit_get_ticks(); }

uint32_t timer_get_elapsed_milliseconds() {
  return pit_get_ticks() - start_ticks;
}
