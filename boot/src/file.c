#include <file.h>

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FS_PROTOCOL;
EFI_LOADED_IMAGE_PROTOCOL *ROOT_IMAGE;

EFI_FILE *load_file(EFI_FILE *Directory, CHAR16 *Path, EFI_HANDLE Image) {
  EFI_FILE *LoadedFile;
  EFI_GUID EfiImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
  EFI_GUID EfiSimpleFsProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

  if (ROOT_IMAGE == NULL || FS_PROTOCOL == NULL) {
    uefi_call_wrapper(BS->HandleProtocol, 3, Image, &EfiImageProtocolGuid, (void **)&ROOT_IMAGE);
    uefi_call_wrapper(BS->HandleProtocol, 3, ROOT_IMAGE->DeviceHandle, &EfiSimpleFsProtocolGuid, (void **)&FS_PROTOCOL);
  }

  if (Directory == NULL)
    uefi_call_wrapper(FS_PROTOCOL->OpenVolume, 2, FS_PROTOCOL, &Directory);

  uefi_call_wrapper(Directory->Open, 5, Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);

  return LoadedFile;
}
