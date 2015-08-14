// blue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

#define obf(c) (c) + 2015
#define decodeobf(str) do{char *p = str; while (*p) *p++ -= 2015;} while(0);

void Detected()
{
	printf(" detected! Press any key.");
	getchar();
	exit(0);
}

static inline int Blue()
{
	printf("\n[Level 1] Blue ...");
	Sleep(360000);
	DWORD time1 = GetTickCount();
	Sleep(500);
	if ((GetTickCount() - time1) < 450)	Detected();
	else return 0;
}

static inline int Charlie()
{
	printf("\n[Level 2] Charlie ...");
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	if (siSysInfo.dwNumberOfProcessors < 2) Detected();
	else return 0;
}

static inline int Delta()
{
	printf("\n[Level 3] Delta ...");
	unsigned long NumberOfProcessors = 0;
	__asm
	{
		mov eax, fs:[0x30]
		mov eax, [eax + 0x64]
		mov NumberOfProcessors, eax
	}
	if (NumberOfProcessors & 0x1) Detected();
	else return 0;
}

static inline int Echo()
{
	printf("\n[Level 4] Echo ...");
	__try{__asm{cmpxchg8b fs:[0x1000]}}
	__except (1){Detected();}
	return 0;
}

void Flag(){
	char flag[] = { obf('O'), obf('n'), obf('l'), obf('y'), obf(' '), obf('t'), obf('h'), obf('e'), obf(' '), obf('P'), obf('a'), obf('r'), obf('a'), obf('n'), obf('o'), obf('i'), obf('d'), obf(' '), obf('S'), obf('u'), obf('r'), obf('v'), obf('i'), obf('v'), obf('e'), 0 };
	decodeobf(flag);
	printf("\n%s\n", flag);
	getchar();
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Some anti QEMU trick used by in-the-wild malware.\n");
	if (IsDebuggerPresent() == FALSE && Blue() == 0 && Charlie() == 0 && Delta() == 0 && Echo() == 0)
		Flag();
	return 0;
}
