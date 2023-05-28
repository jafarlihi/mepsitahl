#ifndef OS_CONSOLE_HPP
#define OS_CONSOLE_HPP

#include "boot.hpp"
#include <stdint.h>

class Console {
  public:
    Console() {
      this->x_position = 0;
      this->y_position = 0;
    }

    Console(FrameBuffer *framebuffer, PSF1_Font *font) {
      this->init(framebuffer, font);
      this->x_position = 0;
      this->y_position = 0;
    }

    void init(FrameBuffer *framebuffer, PSF1_Font *font);
    void print_line(char *str);
    void put_char(char c, uint32_t x, uint32_t y, uint32_t color);
    void clear_screen(uint32_t color);

  private:
    void new_line(void);

    FrameBuffer *framebuffer;
    PSF1_Font *font;
    uint32_t x_position;
    uint32_t y_position;
};

extern Console console;

#endif
