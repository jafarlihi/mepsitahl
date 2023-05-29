#pragma once

#include <stddef.h>
#include <stdint.h>

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
char *strcat(char *d, const char *s);
char *strcpy(char *d, const char *s);
size_t strlen(const char *str);
int isdigit(char c);
uint64_t extract_bit_chunk(uint8_t bit_from, uint8_t bit_to, uint64_t field);
bool string_ends_with(const char *str, const char *end);
