#include "heap.h"

extern uint8_t heap_start;
extern uint8_t heap_end;

uint8_t *heap_top = &heap_start;
uint8_t *heap_bottom = &heap_end;

void *heap_memory_allocate(size_t size) {
  size = (size + 7) & ~7;
  if (heap_top + size > heap_bottom)
    return NULL;
  void *ptr = heap_top;
  heap_top += size;
  return ptr;
}
