#include "mem.h"

void *memset(void *dest, char val, uint32_t count) {
  char *temp = (char *)dest;
  for (; count != 0; count--) {
    *temp++ = val;
  }
  return dest;
}

void *memcpy(void *dest, const void *src, uint32_t count) {
  char *dst8 = (char *)dest;
  const char *src8 = (const char *)src;
  while (count--) {
    *dst8++ = *src8++;
  }
  return dest;
}
