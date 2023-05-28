#ifndef OS_LIBK_H
#define OS_LIBK_H

#include <stddef.h>
#include <stdint.h>

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

void* memcpy(void *dstptr, const void *srcptr, size_t size);
void *memmove(void *d, const void *s, size_t size);
void *memset(void *buf, int value, size_t size);
char *strcat(char *d, const char *s);
char *strcpy(char *d, const char *s);
size_t strlen(const char *str);
int isdigit(char c);
uint64_t extract_bit_chunk(uint8_t bit_from, uint8_t bit_to, uint64_t field);

#endif
