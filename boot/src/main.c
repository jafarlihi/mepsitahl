#include <efi.h>
#include <efilib.h>
#include <elf.h>

#include <boot.h>
#include <file.h>
#include <utils.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE Image, EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(Image, SystemTable);
  CHAR16 *kernel_name = L"kernel.elf";
  EFI_FILE *kernel = load_file(NULL, kernel_name, Image);
  EFI_GUID FileInfoGuid = EFI_FILE_INFO_ID;

  if (kernel == NULL) {
    Print(L"ERROR: Kernel file couldn't be loaded\r\n");
    return EFI_ERROR(L"Kernel file couldn't be loaded\r\n");
  }

  Elf64_Ehdr header;
  {
    UINTN FileInfoSize;
    EFI_FILE_INFO *FileInfo;
    uefi_call_wrapper(kernel->GetInfo, 4, kernel, &FileInfoGuid, &FileInfoSize, NULL);
    uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, FileInfoSize, (void **)&FileInfo);
    uefi_call_wrapper(kernel->GetInfo, 4, kernel, &FileInfoGuid, &FileInfoSize, (void **)&FileInfo);

    UINTN size = sizeof(header);
    uefi_call_wrapper(kernel->Read, 3, kernel, &size, &header);
  }

  if (memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
      header.e_ident[EI_CLASS] != ELFCLASS64 ||
      header.e_ident[EI_DATA] != ELFDATA2LSB ||
      header.e_type != ET_EXEC ||
      header.e_machine != EM_X86_64 ||
      header.e_version != EV_CURRENT) {
    Print(L"ERROR: ELF file is invalid");
    return EFI_ERROR(L"ELF file is invalid");
  } else Print((CHAR16 *)L"Kernel has valid headers\r\n");

  Elf64_Phdr *phdrs;
  {
    uefi_call_wrapper(kernel->SetPosition, 2, kernel, header.e_phoff);
    UINTN size = header.e_phnum * header.e_phentsize;
    uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, size, (void **)&phdrs);
    uefi_call_wrapper(kernel->Read, 3, kernel, &size, phdrs);
  }

  for (Elf64_Phdr *phdr = phdrs;
      (char *)phdr < (char *)phdrs + header.e_phnum * header.e_phentsize;
      phdr = (Elf64_Phdr *)((char *)phdr + header.e_phentsize)) {
    switch (phdr->p_type) {
      case PT_LOAD: {
                      int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
                      Elf64_Addr segment = phdr->p_paddr;
                      uefi_call_wrapper(BS->AllocatePages, 4, AllocateAddress, EfiLoaderData, pages, &segment);
                      uefi_call_wrapper(kernel->SetPosition, 2, kernel, phdr->p_offset);
                      UINTN size = phdr->p_filesz;
                      uefi_call_wrapper(kernel->Read, 3, kernel, &size, (void *)segment);
                      break;
                    }
    }
  }

  Print(L"Loaded program\r\n");
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = get_gop();
  if (gop == NULL) return EFI_PROTOCOL_ERROR;

  Print((CHAR16 *)L"Loaded GOP\r\n");
  FrameBuffer *buff = new_framebuffer(gop);

  PSF1_Font *font = load_font(NULL, (CHAR16 *) L"zap-light16.psf", Image);
  if (font == NULL) {
    Print((CHAR16 *) L"ERROR: Font file is invalid.\r\n");
    return EFI_LOAD_ERROR;
  }
  Print((CHAR16 *)L"Loaded font\r\n");

  BootInfo *boot_info;
  {
    UINTN size = sizeof(BootInfo);
    uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, size, (void **)&boot_info);
    boot_info->framebuffer = buff;
    boot_info->psf1_font = font;
  }

  if (boot_info == NULL) {
    Print(L"ERROR: Boot information is missing");
    return EFI_ERROR(L"Boot information is missing");
  }

  // TODO: Error checking
  UINTN mapSize = 0, mapKey, descriptorSize;
  EFI_MEMORY_DESCRIPTOR *memoryMap = NULL;
  EFI_STATUS result;
  UINT32 descriptorVersion;
  result = uefi_call_wrapper((void *)SystemTable->BootServices->GetMemoryMap, 5, &mapSize, &memoryMap, NULL, &descriptorSize, NULL);
  mapSize += 2 * descriptorSize;
  result = uefi_call_wrapper((void *)SystemTable->BootServices->AllocatePool, 3, EfiLoaderData, mapSize, (void **)&memoryMap);
  result = uefi_call_wrapper((void *)SystemTable->BootServices->GetMemoryMap, 5, &mapSize, &memoryMap, &mapKey, &descriptorSize, &descriptorVersion);
  result = uefi_call_wrapper((void *)SystemTable->BootServices->ExitBootServices, 2, Image, mapKey);

  Print((CHAR16 *)L"Starting kernel\r\n");
  void (*KernelStart)(BootInfo *) = ((__attribute__((sysv_abi)) void (*)(BootInfo *)) header.e_entry);
  KernelStart(boot_info);
  return EFI_SUCCESS;
}
