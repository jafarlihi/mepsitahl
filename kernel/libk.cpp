#include "libk.hpp"
#include <limits.h>

void *memcpy(void *dest, const void *src, size_t n) {
  uint8_t *pdest = (uint8_t *)dest;
  const uint8_t *psrc = (const uint8_t *)src;
  for (size_t i = 0; i < n; i++) pdest[i] = psrc[i];
  return dest;
}

void *memset(void *s, int c, size_t n) {
  uint8_t *p = (uint8_t *)s;
  for (size_t i = 0; i < n; i++) p[i] = (uint8_t)c;
  return s;
}

void *memmove(void *dest, const void *src, size_t n) {
  uint8_t *pdest = (uint8_t *)dest;
  const uint8_t *psrc = (const uint8_t *)src;
  if (src > dest) for (size_t i = 0; i < n; i++) pdest[i] = psrc[i];
  else if (src < dest) for (size_t i = n; i > 0; i--) pdest[i-1] = psrc[i-1];
  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const uint8_t *p1 = (const uint8_t *)s1;
  const uint8_t *p2 = (const uint8_t *)s2;
  for (size_t i = 0; i < n; i++) if (p1[i] != p2[i]) return p1[i] < p2[i] ? -1 : 1;
  return 0;
}

char *strcat(char *d, const char *s) {
  size_t i,j;
  for (i = 0; d[i] != '\0'; i++)
    ;
  for (j = 0; s[j] != '\0'; j++)
    d[i+j] = s[j];
  d[i+j] = '\0';
  return d;
}

char *strcpy(char *d, const char *s) {
  char *temp = d;
  while((*d++ = *s++));
  return temp;
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

int isdigit(char c) {
  return (c>='0') && (c<='9');
}

__attribute__((always_inline)) uint64_t extract_bit_chunk(uint8_t bit_from, uint8_t bit_to, uint64_t field) {
  return (field >> bit_from) & ( UINT64_MAX >> (sizeof(uint64_t) * CHAR_BIT - (bit_to - bit_from + 1)));
}

bool string_ends_with(const char *str, const char *end) {
  const char *_str = str;
  const char *_end = end;
  while (*str != 0)
    str++;
  str--;
  while (*end != 0)
    end++;
  end--;
  while (true) {
    if (*str != *end)
      return false;
    str--;
    end--;
    if (end == _end || (str == _str && end == _end))
      return true;
    if (str == _str)
      return false;
  }
  return true;
}
