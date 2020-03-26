#pragma once
#include<Windows.h>

// These definitions are referenced from UEFI Specification Version 2.8
// See: https://uefi.org/specifications

#define EFI_GLOBAL_VARIABLE TEXT("{8BE4DF61-93CA-11D2-AA0D-00E098032B8C}")
//{0x8BE4DF61,0x93CA,0x11d2,{0xAA,0x0D,0x00,0xE0,0x98,0x03,0x2B,0x8C}}

#define BOOTORDER TEXT("BootOrder")
#define BOOTCUR TEXT("BootCurrent")
#define BOOTNEXT TEXT("BootNext")
#ifdef UNICODE
wchar_t __bootitem[9] = { 0 };
#define BOOTITEM(x) (wsprintf_s(__bootitem, 9, L"Boot%04X", x), __bootitem)
#else
char __bootitem[9] = { 0 };
#define BOOTITEM(x) (sprintf_s(__bootitem, 9, "Boot%04X", x), __bootitem)
#endif

#define LOAD_OPTION_ACTIVE 0x00000001
#define LOAD_OPTION_FORCE_RECONNECT 0x00000002
#define LOAD_OPTION_HIDDEN 0x00000008
#define LOAD_OPTION_CATEGORY 0x00001F00
#define LOAD_OPTION_CATEGORY_BOOT 0x00000000
#define LOAD_OPTION_CATEGORY_APP 0x00000100

typedef struct _EFI_LOAD_OPTION_HEADER {
	UINT32 Attributes;
	UINT16 FilePathListLength;
	// CHAR16 Description[];
	// EFI_DEVICE_PATH_PROTOCOL FilePathList[];
	// UINT8 OptionalData[];
} EFI_LOAD_OPTION_HEADER;

/*
Type 0x01 - Hardware Device Path
Type 0x02 - ACPI Device Path
Type 0x03 - Messaging Device Path
Type 0x04 - Media Device Path
Type 0x05 - BIOS Boot Specification Device Path
Type 0x7F - End of Hardware Device Path

Type 0x7F
	Sub-Type 0xFF - End Entire Device Path, or
	Sub-Type 0x01 - End This Instance of a Device Path and start a new Device
Path
*/
typedef struct _EFI_DEVICE_PATH_PROTOCOL {
	UINT8 Type;
	UINT8 SubType;
	UINT8 Length[2];
	// CHAR PATH[];
} EFI_DEVICE_PATH_PROTOCOL;