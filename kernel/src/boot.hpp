#ifndef OS_BOOT_HPP
#define OS_BOOT_HPP

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
  void *FrameBufferBase;
  unsigned long FrameBufferSize;
  unsigned int HorizontalRes;
  unsigned int VerticalRes;
  unsigned int PixelsPerScanLine;
} FrameBuffer;

typedef struct {
  PSF1_Font *psf1_font;
  FrameBuffer *framebuffer;
} BootInfo;

#endif
