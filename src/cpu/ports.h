#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
  __asm__ __volatile__("outb %b0, %w1" ::"a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}
