#include "ports.hpp"

unsigned char inb(unsigned short port) {
  unsigned char rv;
  asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
  return rv;
}

void outb(unsigned short port, unsigned char data) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}
