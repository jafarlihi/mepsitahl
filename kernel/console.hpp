#pragma once

#include <stdint.h>

typedef struct {
  unsigned char magic[2];
  unsigned char mode;
  unsigned char charsize;
} PSF1_Header;

typedef struct {
  PSF1_Header *psf_header;
  void *glyph_buffer;
} PSF1_Font;

typedef struct {
  void *base;
  unsigned long size;
  unsigned int horizontal_res;
  unsigned int vertical_res;
  unsigned int pixels_per_scanline;
} FrameBuffer;

class Console {
  public:
    Console() {
      this->x_position = 0;
      this->y_position = 0;
    }

    Console(FrameBuffer framebuffer, PSF1_Font font) {
      this->init(framebuffer, font);
      this->x_position = 0;
      this->y_position = 0;
    }

    void init(FrameBuffer framebuffer, PSF1_Font font);
    void print_line(char *str);
    void put_char(char c, uint32_t x, uint32_t y, uint32_t color);
    void clear_screen(uint32_t color);

  private:
    void new_line(void);

    FrameBuffer framebuffer;
    PSF1_Font font;
    uint32_t x_position;
    uint32_t y_position;
};

extern Console *console;
