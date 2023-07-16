#pragma once

#include <stdint.h>

#define EFI_ERROR(x) (((intptr_t)(x)) < 0)
#define EFI_SUCCESS 0u

typedef void VOID;
typedef unsigned long UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef unsigned short CHAR16;
typedef uint8_t BOOLEAN;

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;
typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;

#define EFIAPI __attribute__((ms_abi))

typedef struct {
  UINT32 Guid1;
  UINT16 Guid2;
  UINT16 Guid3;
  UINT8 Guid4[8];
} EFI_GUID;

typedef struct {
  UINT64 Signature;
  UINT32 Revision;
  UINT32 HeaderSize;
  UINT32 CRC32;
  UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef enum {
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress,
  MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct {
  UINT32 Type;
  EFI_PHYSICAL_ADDRESS PhysicalStart;
  EFI_VIRTUAL_ADDRESS VirtualStart;
  UINT64 NumberOfPages;
  UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef enum {
  AllHandles,
  ByRegisterNotify,
  ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum {
  EfiReservedMemoryType,
  EfiLoaderCode,
  EfiLoaderData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiConventionalMemory,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiPersistentMemory,
  EfiMaxMemoryType,
  EfixMinOemMemoryType = 0x70000000,
  EfixMaxOemMemoryType = 0x7fffffff,
  EfixMinOsMemoryType = INT32_MIN,
  EfixMaxOsMemoryType = -1,
} EFI_MEMORY_TYPE;

typedef struct EFI_BOOT_SERVIES EFI_BOOT_SERVICES;
typedef struct EFI_CONFIGURATION_TABLE EFI_CONFIGURATION_TABLE;
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;

typedef VOID(EFIAPI *EFIX_UNUSED_FUNC)(VOID);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_RESET)(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_STRING)(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_TEST_STRING)(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_PAGES)(EFI_ALLOCATE_TYPE Type,
                                               EFI_MEMORY_TYPE MemoryType,
                                               UINTN Pages,
                                               EFI_PHYSICAL_ADDRESS *Memory);

typedef EFI_STATUS(EFIAPI *EFI_FREE_PAGES)(EFI_PHYSICAL_ADDRESS Memory,
                                           UINTN Pages);

typedef EFI_STATUS(EFIAPI *EFI_GET_MEMORY_MAP)(UINTN *MemoryMapSize,
                                               EFI_MEMORY_DESCRIPTOR *MemoryMap,
                                               UINTN *MapKey,
                                               UINTN *DescriptorSize,
                                               UINT32 *DescriptorVersion);

typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_POOL)(EFI_MEMORY_TYPE PoolType,
                                              UINTN Size, VOID **Buffer);

typedef EFI_STATUS(EFIAPI *EFI_FREE_POOL)(VOID *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE)(EFI_LOCATE_SEARCH_TYPE SearchType,
                                              EFI_GUID *Protocol,
                                              VOID *SearchKey,
                                              UINTN *BufferSize,
                                              EFI_HANDLE *Buffer);

typedef EFI_STATUS(EFIAPI *EFI_EXIT)(EFI_HANDLE ImageHandle,
                                     EFI_STATUS ExitStatus, UINTN ExitDataSize,
                                     CHAR16 *ExitData);

typedef EFI_STATUS(EFIAPI *EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE ImageHandle,
                                                   UINTN MapKey);

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)(UINT64 *Count);

typedef EFI_STATUS(EFIAPI *EFI_SET_WATCHDOG_TIMER)(UINTN Timeout,
                                                   UINT64 WatchdogCode,
                                                   UINTN DataSize,
                                                   CHAR16 *WatchdogData);

typedef EFI_STATUS(EFIAPI *EFI_STALL)(UINTN Microseconds);

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL)(
    EFI_HANDLE Handle, EFI_GUID *Protocol, VOID **Interface,
    EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);

typedef EFI_STATUS(EFIAPI *EFI_CLOSE_PROTOCOL)(EFI_HANDLE Handle,
                                               EFI_GUID *Protocol,
                                               EFI_HANDLE AgentHandle,
                                               EFI_HANDLE ControllerHandle);

typedef EFI_STATUS(EFIAPI *EFI_PROTOCOLS_PER_HANDLE)(
    EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE_BUFFER)(
    EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, VOID *SearchKey,
    UINTN *NoHandles, EFI_HANDLE **Buffer);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_PROTOCOL)(EFI_GUID *Protocol,
                                                VOID *Registration,
                                                VOID **Interface);

typedef VOID(EFIAPI *EFI_COPY_MEM)(VOID *Destination, VOID *Source,
                                   UINTN Length);

typedef VOID(EFIAPI *EFI_SET_MEM)(VOID *Buffer, UINTN Size, UINT8 Value);

typedef EFI_STATUS(EFIAPI *EFI_CALCULATE_CRC32)(VOID *Data, UINTN DataSize,
                                                UINT32 *Crc32);

struct EFI_BOOT_SERVIES {
  EFI_TABLE_HEADER Hdr;

  EFIX_UNUSED_FUNC RaiseTPL;
  EFIX_UNUSED_FUNC RestoreTPL;

  EFI_ALLOCATE_PAGES AllocatePages;
  EFI_FREE_PAGES FreePages;
  EFI_GET_MEMORY_MAP GetMemoryMap;
  EFI_ALLOCATE_POOL AllocatePool;
  EFI_FREE_POOL FreePool;

  EFIX_UNUSED_FUNC CreateEvent;
  EFIX_UNUSED_FUNC SetTimer;
  EFIX_UNUSED_FUNC WaitForEvent;
  EFIX_UNUSED_FUNC SignalEvent;
  EFIX_UNUSED_FUNC CloseEvent;
  EFIX_UNUSED_FUNC CheckEvent;

  EFIX_UNUSED_FUNC InstallProtocolInterface;
  EFIX_UNUSED_FUNC ReinstallProtocolInterface;
  EFIX_UNUSED_FUNC UninstallProtocolInterface;
  EFIX_UNUSED_FUNC HandleProtocol;
  VOID *Reserved;
  EFIX_UNUSED_FUNC RegisterProtocolNotify;
  EFI_LOCATE_HANDLE LocateHandle;
  EFIX_UNUSED_FUNC LocateDevicePath;
  EFIX_UNUSED_FUNC InstallConfigurationTable;

  EFIX_UNUSED_FUNC LoadImage;
  EFIX_UNUSED_FUNC StartImage;
  EFI_EXIT Exit;
  EFIX_UNUSED_FUNC UnloadImage;
  EFI_EXIT_BOOT_SERVICES ExitBootServices;

  EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
  EFI_STALL Stall;
  EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

  EFIX_UNUSED_FUNC ConnectController;
  EFIX_UNUSED_FUNC DisconnectController;

  EFI_OPEN_PROTOCOL OpenProtocol;
  EFI_CLOSE_PROTOCOL CloseProtocol;
  EFIX_UNUSED_FUNC OpenProtocolInformation;

  EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
  EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
  EFI_LOCATE_PROTOCOL LocateProtocol;
  EFIX_UNUSED_FUNC InstallMultipleProtocolInterfaces;
  EFIX_UNUSED_FUNC UninstallMultipleProtocolInterfaces;

  EFI_CALCULATE_CRC32 CalculateCrc32;
  EFI_COPY_MEM CopyMem;
  EFI_SET_MEM SetMem;
  EFIX_UNUSED_FUNC CreateEventEx;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  EFI_TEXT_RESET Reset;
  EFI_TEXT_STRING OutputString;
  EFI_TEXT_TEST_STRING TestString;
  EFIX_UNUSED_FUNC QueryMode;
  EFIX_UNUSED_FUNC SetMode;
  EFI_TEXT_SET_ATTRIBUTE SetAttribute;
  EFI_TEXT_CLEAR_SCREEN ClearScreen;
  EFIX_UNUSED_FUNC SetCursorPosition;
  EFIX_UNUSED_FUNC EnableCursor;
  VOID *Mode;
};

struct EFI_CONFIGURATION_TABLE {
  EFI_GUID VendorGuid;
  VOID *VendorTable;
};

struct EFI_SYSTEM_TABLE {
  EFI_TABLE_HEADER Hdr;
  CHAR16 *FirmwareVendor;
  UINT32 FirmwareRevision;
  EFI_HANDLE ConsoleInHandle;
  VOID *ConIn;
  EFI_HANDLE ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
  EFI_HANDLE StandardErrorHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
  VOID *RuntimeServices;
  EFI_BOOT_SERVICES *BootServices;
  UINTN NumberOfTableEntries;
  EFI_CONFIGURATION_TABLE *ConfigurationTable;
};