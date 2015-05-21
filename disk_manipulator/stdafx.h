// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <winternl.h>

#define DllExport __declspec(dllexport)


/* WinAPI internal declerations start */
typedef NTSTATUS(NTAPI *P_NtOpenFile) (
	OUT PHANDLE FileHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG ShareAccess,
	IN ULONG OpenOptions
	);

typedef HANDLE(WINAPI *P_GetClipboardData) (
	IN UINT uFormat
	);
/* WinAPI internal declerations end */



/* SbieAPI DLL start */
typedef LONG(__stdcall *P_SbieApi_EnumBoxes)(
	LONG index,                 // initialize to -1
	WCHAR *box_name);           // pointer to WCHAR [34]

typedef LONG(__stdcall *P_SbieApi_QueryBoxPath)(
	const WCHAR *box_name,      // pointer to WCHAR [34]
	WCHAR *file_path,
	WCHAR *key_path,
	WCHAR *ipc_path,
	ULONG *file_path_len,
	ULONG *key_path_len,
	ULONG *ipc_path_len);

typedef LONG(__stdcall *P_SbieApi_QueryProcessPath)(
	HANDLE process_id,
	WCHAR *file_path,
	WCHAR *key_path,
	WCHAR *ipc_path,
	ULONG *file_path_len,
	ULONG *key_path_len,
	ULONG *ipc_path_len);

typedef LONG(__stdcall *P_SbieApi_QueryProcessPath)(
	HANDLE process_id,
	WCHAR *file_path,
	WCHAR *key_path,
	WCHAR *ipc_path,
	ULONG *file_path_len,
	ULONG *key_path_len,
	ULONG *ipc_path_len);

typedef LONG(__stdcall *P_SbieApi_QueryProcess)(
	HANDLE process_id,
	WCHAR *box_name,            // pointer to WCHAR [34]
	WCHAR *image_name,          // pointer to WCHAR [96]
	WCHAR *sid_string,          // pointer to WCHAR [96]
	ULONG *session_id);

typedef BOOLEAN(__stdcall *P_SbieDll_KillOne)(
	HANDLE process_id);

typedef BOOLEAN(__stdcall *P_SbieDll_KillAll)(
	ULONG session_id,
	const WCHAR *box_name);

typedef LONG(__stdcall *P_SbieApi_QueryConf)(
	const WCHAR *section_name,  // pointer to WCHAR [34]
	const WCHAR *setting_name,  // pointer to WCHAR [66]
	ULONG setting_index,
	WCHAR *value,
	ULONG value_len);

typedef LONG(__stdcall *P_SbieDll_UpdateConf)(
	WCHAR operation_code,
	const WCHAR *password,      // limited to 64 chars
	const WCHAR *section_name,  // limited to 32 chars
	const WCHAR *setting_name,  // limited to 64 chars
	const WCHAR *value);         // limited to 2000 chars

typedef LONG(__stdcall *P_SbieApi_ReloadConf)(
	ULONG session_id);

typedef void *(__stdcall *P_SbieDll_Hook)(
	const char *name,
	void *source_func,
	void *detour_func);

typedef void(__stdcall *P_DllCallback)(const WCHAR *ImageName, HMODULE ImageBase);
typedef BOOLEAN *(__stdcall *P_SbieDll_RegisterDllCallback)(
	P_DllCallback pCallback);

typedef LONG *(__stdcall *P_SbieApi_GetHomePath)(
	WCHAR *NtPath,
	ULONG NtPathMaxLen,
	WCHAR *DosPath,
	ULONG DosPathMaxLen
	);
/* SbieAPI DLL end */


