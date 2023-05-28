#include <font.h>
#include <file.h>

int is_valid_psf1_header(PSF1_Header *header) {
  if (header->magic[0] != PSF_MAGIC0 || header->magic[1] != PSF_MAGIC1) return 1;
  return 0;
}

PSF1_Header *load_psf1_header(EFI_FILE *font_file) {
  PSF1_Header *header;
  uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, sizeof(PSF1_Header), (void **)&header);
  UINTN header_size = sizeof(PSF1_Header);
  uefi_call_wrapper(font_file->Read, 3, font_file, &header_size, header);
  return header;
}

void* load_glyph_buffer(EFI_FILE *font_file, UINTN gb_size) {
  void *glyph_buffer;
  uefi_call_wrapper(font_file->SetPosition, 2, font_file, sizeof(PSF1_Header));
  uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, gb_size, (void **) &glyph_buffer);
  uefi_call_wrapper(font_file->Read, 3, font_file, &gb_size, glyph_buffer);
  return glyph_buffer;
}

PSF1_Font* load_font(EFI_FILE *dir, CHAR16 *path, EFI_HANDLE image) {
  EFI_FILE *font = load_file(dir, path, image);
  if (font == NULL)
    return NULL;

  PSF1_Header *psf1_header = load_psf1_header(font);
  if (is_valid_psf1_header(psf1_header) > 0)
    return NULL;

  UINTN glyph_buffer_size = psf1_header->charsize * 256;
  if (psf1_header->mode == 1)
    glyph_buffer_size = psf1_header->charsize * 512;

  void *glyph_buffer = load_glyph_buffer(font, glyph_buffer_size);

  PSF1_Font *built_font;
  {
    uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, sizeof(PSF1_Font), (void **) &built_font);
  }
  built_font->psf_header = psf1_header;
  built_font->glyph_buffer = glyph_buffer;
  return built_font;
}
