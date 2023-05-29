#include "console.hpp"
#include "libk.hpp"

void Console::init(FrameBuffer framebuffer, PSF1_Font font) {
  this->framebuffer = framebuffer;
  this->font = font;
}

void Console::new_line(void) {
  this->x_position = 0;
  this->y_position += 16;
}

void Console::print_line(char *str) {
  for (uint32_t i = 0; i < strlen(str); i++) {
    this->put_char(str[i], this->x_position, this->y_position, 0xFFFFFFFF);
    this->x_position += 8;
    if (this->x_position >= this->framebuffer.pixels_per_scanline)
      this->new_line();
  }
}

void Console::put_char(char c, uint32_t x, uint32_t y, uint32_t color) {
  uint32_t x_offset = x;
  uint32_t y_offset = y;

  uint32_t *pixel = (uint32_t *)this->framebuffer.base;
  char *glyph = (char *)this->font.glyph_buffer + (c * this->font.psf_header->charsize);

  for (uint32_t y = y_offset; y < y_offset + 16; y++) {
    for (uint32_t x = x_offset; x < x_offset + 8; x++) {
      if ((*glyph & (0b10000000 >> (x - x_offset))) > 0)
        *(pixel + x + (y * this->framebuffer.pixels_per_scanline)) = color;
    }
    glyph++;
  }
}

void Console::clear_screen(uint32_t color) {
  uint32_t *pixel = (uint32_t *)this->framebuffer.base;
  for (uint64_t i = 0; i < this->framebuffer.horizontal_res * this->framebuffer.vertical_res; i++)
    *(pixel + i) = color;
}
