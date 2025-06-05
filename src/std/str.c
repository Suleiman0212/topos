#include "str.h"

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, unsigned int n) {
  while (n && *s1 && (*s1 == *s2)) {
    s1++;
    s2++;
    n--;
  }
  if (n == 0)
    return 0;
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

char *strcpy(char *dest, const char *src) {
  char *d = dest;
  while ((*d++ = *src++) != '\0')
    ;
  return dest;
}

unsigned int strlen(const char *str) {
  unsigned int len = 0;
  while (str[len])
    len++;
  return len;
}

int atoi(const char *str) {
  int result = 0;
  int sign = 1;

  if (*str == '-') {
    sign = -1;
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }

  return result * sign;
}

char *itoa(int value, char *str, int base) {
  char *ptr = str, *ptr1 = str, tmp_char;
  int tmp_value;
  int is_negative = 0;

  if (value == 0) {
    *ptr++ = '0';
    *ptr = '\0';
    return str;
  }

  if (value < 0 && base == 10) {
    is_negative = 1;
    value = -value;
  }

  while (value != 0) {
    tmp_value = value % base;
    *ptr++ = (tmp_value < 10) ? (tmp_value + '0') : (tmp_value - 10 + 'a');
    value /= base;
  }

  if (is_negative)
    *ptr++ = '-';

  *ptr-- = '\0';

  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }

  return str;
}
