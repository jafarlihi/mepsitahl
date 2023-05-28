#ifndef BOOTLOADER_BOOT_H
#define BOOTLOADER_BOOT_H

#include <font.h>
#include <graphics.h>

typedef struct {
  PSF1_Font *psf1_font;
  FrameBuffer *framebuffer;
} BootInfo;

#endif
