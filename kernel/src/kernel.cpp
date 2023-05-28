#include "boot.hpp"
#include "console.hpp"
#include "idt.hpp"
#include "serial.hpp"

extern "C" void _start(BootInfo *boot) {
  asm volatile ("cli");
  init_serial();
  write_serial_line("Serial initiated");
  init_idt();
  console.init(boot->framebuffer, boot->psf1_font);
  console.clear_screen(0x00000000);
  console.print_line("mr henlo!");
  __asm__("hlt");
}
