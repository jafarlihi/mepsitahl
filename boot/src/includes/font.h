#ifndef BOOTLOADER_FONT_H
#define BOOTLOADER_FONT_H

#include <efi.h>
#include <efilib.h>

#define PSF_MAGIC0 0x36
#define PSF_MAGIC1 0x04

typedef struct {
  unsigned char magic[2];
  unsigned char mode;
  unsigned char charsize;
} PSF1_Header;

typedef struct {
  PSF1_Header *psf_header;
  void *glyph_buffer;
} PSF1_Font;

PSF1_Font *load_font(EFI_FILE *dir, CHAR16 *path, EFI_HANDLE image);

#endif
