#include <stdint.h>
#include <stddef.h>
#include "limine.h"
#include "libk.hpp"
#include "console.hpp"
#include "idt.hpp"

void *operator new(size_t bytes, void *ptr) { return ptr; };

Console *console;

static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

struct limine_internal_module font_module = {
  .path = "./zap-light16.psf",
  .cmdline = "zap-light16.psf module"
};

struct limine_internal_module *internal_modules[] = {
  &font_module,
};

static volatile struct limine_module_request module_request = {
  .id = LIMINE_MODULE_REQUEST,
  .revision = 1,
  .response = NULL,
  .internal_module_count = 1,
  .internal_modules = internal_modules
};

struct limine_file *get_limine_file(const char *name) {
  struct limine_module_response *module_response = module_request.response;
  for (size_t i = 0; i < module_response->module_count; i++) {
    struct limine_file *f = module_response->modules[i];
    if (string_ends_with(f->path, name))
      return f;
  }
  return NULL;
}

static void hcf(void) {
  asm ("cli");
  for (;;) {
    asm ("hlt");
  }
}

extern "C" void _start(void) {
  if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) hcf();
  struct limine_framebuffer *limine_framebuffer = framebuffer_request.response->framebuffers[0];
  FrameBuffer framebuffer;
  framebuffer.base = limine_framebuffer->address;
  framebuffer.size = limine_framebuffer->height * limine_framebuffer->pitch;
  framebuffer.horizontal_res = limine_framebuffer->width;
  framebuffer.vertical_res = limine_framebuffer->height;
  framebuffer.pixels_per_scanline = limine_framebuffer->pitch / 4;

  if (module_request.response == NULL) hcf();
  PSF1_Font font;
  const char *font_name = "zap-light16.psf";
  struct limine_file *file = get_limine_file(font_name);
  if (file == NULL) hcf();
  font.psf_header = (PSF1_Header *)file->address;
  if (font.psf_header->magic[0] != 0x36 || font.psf_header->magic[1] != 0x04) hcf();
  font.glyph_buffer = (void *)((uint64_t)file->address + sizeof(PSF1_Header));

  alignas(Console) char console_memory[sizeof(Console)];
  console = new (console_memory) Console(framebuffer, font);
  console->print_line("Henlo der");

  init_idt();

  hcf();
}
