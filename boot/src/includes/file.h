#ifndef BOOTLOADER_FILE_H
#define BOOTLOADER_FILE_H

#include <efi.h>
#include <efilib.h>

EFI_FILE *load_file(EFI_FILE *dir, CHAR16 *path, EFI_HANDLE image);

#endif
