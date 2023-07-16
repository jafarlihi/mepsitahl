#include <efi.h>
#include <stdbool.h>
#include <stddef.h>

#define ERR(x)                                                                 \
  if (EFI_ERROR((x)))                                                          \
  return (x)

EFI_STATUS load_image(CHAR16 *path) {
  
}

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
  EFI_STATUS status;

  status = system_table->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
  ERR(status);

  status = system_table->ConOut->ClearScreen(system_table->ConOut);
  ERR(status);

  status =
      system_table->ConOut->OutputString(system_table->ConOut, L"Hello der");
  ERR(status);

  __asm__ volatile("cli\n\t"
                   "hlt\n\t");

  return EFI_SUCCESS;
}