#include<stdio.h>
#include<Windows.h>
#include "efi.h"

DWORD AdjustPermission(char * perm)
{
	HANDLE token;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LUID luid;
		LookupPrivilegeValue(NULL, perm, &luid);
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(token, FALSE, &tp, 0, NULL, NULL);
		if (GetLastError() != ERROR_SUCCESS)
			return -1;
		else
			return 0;
	}
	else
		return -1;
}

int ShowErrorMsg()
{
	DWORD errid = GetLastError();
	if (errid == ERROR_SUCCESS)
		return errid;
	char* msg;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errid,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)& msg,
		0, NULL
	);
	//printf("Error: %d - %s", errid, msg);
	MessageBoxA(NULL, msg, "Error", 0);
	return errid;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	AdjustPermission(SE_SYSTEM_ENVIRONMENT_NAME);
	UINT8 datas[1024] = { 0 };
	UINT16 bootlist[1024] = { 0 };
	wchar_t* bootname = (wchar_t *)&datas[6];

	unsigned int size = GetFirmwareEnvironmentVariable(
		BOOTORDER,
		EFI_GLOBAL_VARIABLE,
		bootlist,
		sizeof(bootlist)
	);
	if (size == 0)
	{
		ShowErrorMsg();
		return -1;
	}
	unsigned int i;
	for (i = 0; i < size / sizeof(UINT16); i++)
	{
		unsigned int ret = GetFirmwareEnvironmentVariable(
			BOOTITEM(bootlist[i]),
			EFI_GLOBAL_VARIABLE,
			datas,
			sizeof(datas)
		);
		if (ret == 0)
		{
			ShowErrorMsg();
			return -1;
		}
		if (wcsncmp(L"Android", bootname, 7) == 0)
		{
			int ret = SetFirmwareEnvironmentVariable(BOOTNEXT, EFI_GLOBAL_VARIABLE, &bootlist[i], sizeof(UINT16));
			if (ret == 0)
			{
				ShowErrorMsg();
				return -1;
			}
			ShellExecute(NULL, "open", "cmd.exe", "/c shutdown -r -t 0", NULL, SW_HIDE);
			break;
		}
	}
	if (i == size / size / sizeof(UINT16))
	{
		MessageBox(NULL, "Cannot find Androidx86 Bootitem", "Error", 0);
	}
	return 0;
}