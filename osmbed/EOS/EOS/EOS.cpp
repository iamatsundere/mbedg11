// EOS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "EOS.h"
#include "stdlib.h"
#include "utils.h"

int x = 0;
int turnT = 1;

DWORD WINAPI writeFunc(void *params) {
	char* st = (char*)params;
	while (true)
	{
		if (x % 2 == 0)
		{
			printf("%s %d\n", st, x*x);
			get_current_time();

			x += 1;
			Sleep(10);
			turnT += 1;
		}
	}
	return 0;
}

DWORD WINAPI readFunc(void *params) {
	char* st = (char*)params;
	while (true)
	{
		if (x % 2 != 0)
		{
			printf("%s %d\n", st, x*x);
			get_current_time();
			x += 1;
			Sleep(10);
			turnT += 1;
		}
	}
	return 0;
}


int main()
{
	DWORD doThreadId;
	HANDLE t1 = CreateThread(NULL, 0, writeFunc, (LPVOID)"WThread", 0, &doThreadId);
	HANDLE t2 = CreateThread(NULL, 0, readFunc, (LPVOID)"RThread", 0, &doThreadId);
	system("PAUSE");
}

