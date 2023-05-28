#include "libk.hpp"
#include <limits.h>

void* memcpy(void *dstptr, const void *srcptr, size_t size) {
  unsigned char *dst = (unsigned char*) dstptr;
  const unsigned char *src = (const unsigned char*) srcptr;
  for (size_t i = 0; i < size; i++) dst[i] = src[i];
  return dstptr;
}

void *memmove(void *d, const void *s, size_t size) {
  unsigned char* dst = (unsigned char *)d;
  const unsigned char *src = (const unsigned char *)s;
  if (dst < src)
    for (size_t i = 0; i < size; i++)
      dst[i] = src[i];
  else
    for (size_t i = size; i != 0; i--)
      dst[i-1] = src[i-1];
  return d;
}

void *memset(void* buf, int value, size_t size) {
  unsigned char* buf_ptr = (unsigned char *)buf;
  for (size_t i = 0; i < size; i++)
    buf_ptr[i] = (unsigned char)value;
  return buf;
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
