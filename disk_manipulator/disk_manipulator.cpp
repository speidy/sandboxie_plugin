// disk_manipulator.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"



/* DLL Globals */
P_NtOpenFile pNtOpenFile = NULL;
P_GetClipboardData pGetClipboardData = NULL;
HMODULE hNTDLL = NULL;
HMODULE hUSER32 = NULL;


NTSTATUS hook_NtOpenFile(
	OUT PHANDLE FileHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG ShareAccess,
	IN ULONG OpenOptions
	)
{
	OutputDebugString(L"NtOpenFile Hook!");
	return pNtOpenFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions);
}

HANDLE WINAPI hook_GetClipboardData(_In_ UINT uFormat)
{
	OutputDebugString(L"Clip hook!");
	return pGetClipboardData(uFormat);
}

DllExport void __stdcall InjectDllMain(HINSTANCE hSbieDll, ULONG_PTR UnusedParameter)
{
	OutputDebugString(L"Hello from Sandbox :)");
		
	if (!hSbieDll) {
		OutputDebugString(L"hSbieDll is nullptr");
		return;
	}

	//
	// locate the addresses of WinAPI functions to be hooked
	//
	hNTDLL = GetModuleHandle(L"ntdll");
	hUSER32 = GetModuleHandle(L"user32");

	if (!(hNTDLL && hUSER32))
	{
		OutputDebugString(L"GetModuleHandle failed");
		return;
	}

	pNtOpenFile = (P_NtOpenFile)GetProcAddress(hNTDLL, "NtOpenFile");
	pGetClipboardData = (P_GetClipboardData)GetProcAddress(hUSER32, "GetClipboardData");

	if (!(pNtOpenFile && pGetClipboardData))
	{
		OutputDebugString(L"Cannot locate addresses via GetProcAddress (winapi)");
		return;
	}

	//
	// locate the address of sandboxie api functions
	//
	P_SbieDll_Hook p_SbieDll_Hook = (P_SbieDll_Hook) GetProcAddress(hSbieDll, "SbieDll_Hook");
	
	if (!p_SbieDll_Hook)
	{
		OutputDebugString(L"Cannot locate addresses via GetProcAddress (sandboxie)");
		return;
	}

	//
	// Fire up the hooks
	//	
	if (!(pNtOpenFile = (P_NtOpenFile)p_SbieDll_Hook("NtOpenFile", pNtOpenFile, hook_NtOpenFile)))
	{
		OutputDebugString(L"SbieDll_Hook: Cannot hook NtOpenFile()");
	}

	if (!(pGetClipboardData = (P_GetClipboardData)p_SbieDll_Hook("GetClipboardData", pGetClipboardData, hook_GetClipboardData))) {
		OutputDebugString(L"SbieDll_Hook: Cannot hook GetClipboardData()");
	}

}
