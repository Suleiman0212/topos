#pragma once

#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, char val, uint32_t count);
void *memcpy(void *dest, const void *src, uint32_t count);
void *malloc(size_t size);
