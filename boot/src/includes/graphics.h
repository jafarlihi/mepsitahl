#ifndef BOOTLOADER_GRAPHICS_H
#define BOOTLOADER_GRAPHICS_H

#include <efi.h>
#include <efilib.h>
#include <efiprot.h>

typedef struct {
  void *base;
  unsigned long size;
  unsigned int x_resolution;
  unsigned int y_resolution;
  unsigned int ppsl;
} FrameBuffer;

typedef struct {
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
  UINTN info_sz;
  UINTN native_mode;
  UINTN num_modes;
} EnhancedVideoModeInfo;

FrameBuffer *new_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop);
EFI_GRAPHICS_OUTPUT_PROTOCOL *get_gop();

#endif
