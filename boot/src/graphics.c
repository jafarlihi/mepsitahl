#include <graphics.h>

FrameBuffer *new_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop) {
  FrameBuffer *buffer = NULL;
  buffer->base = (void *) gop->Mode->FrameBufferBase;
  buffer->size = (unsigned long) gop->Mode->FrameBufferSize;
  buffer->x_resolution = (unsigned int) gop->Mode->Info->HorizontalResolution;
  buffer->y_resolution = (unsigned int) gop->Mode->Info->VerticalResolution;
  buffer->ppsl = (unsigned int) gop->Mode->Info->PixelsPerScanLine;
  return buffer;
}

EFI_GRAPHICS_OUTPUT_PROTOCOL *get_gop() {
  EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

  EFI_STATUS status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void **)&gop);
  if (EFI_ERROR(status)) {
    Print((CHAR16 *)L"Could not locate GOP\n");
    return NULL;
  }

  return gop;
}
