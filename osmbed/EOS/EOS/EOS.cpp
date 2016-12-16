// EOS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "EOS.h"
#include "stdlib.h"

int x = 0;
int turnT = 1;
int NThread = 6;
int oldX = -1;

DWORD WINAPI myFunc(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{

		if (turnT == 1)
		{
			/*if (i == 20)
				break;*/

			x = i*i;
			printf("%s %d\n", st, x);

			turnT += 1;
		}
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI myFunc8(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{
		if (x == oldX)
		{
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
			return 0;
		}

		if (turnT % 2 == 0)
		{
			oldX = x;
			printf("%s %d\n", st, x);
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI myFunc2(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{
		if (x == oldX)
		{
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
			return 0;
		}

		if (turnT % 2 == 0)
		{
			oldX = x;
			printf("%s %d\n", st, x);
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI myFunc4(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{
		if (x == oldX)
		{
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
			return 0;
		}

		if (turnT % 2 == 0)
		{
			oldX = x;
			printf("%s %d\n", st, x);
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI myFunc6(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{
		if (x == oldX)
		{
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
			return 0;
		}

		if (turnT % 2 == 0)
		{
			oldX = x;
			printf("%s %d\n", st, x);
			if (turnT == ((NThread - 1) * 2))
			{
				turnT = 1;
			}
			else
			{
				turnT += 1;
			}
		}
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI myFunc3(void *params) {
	char* st = (char*)params;
	for (int i = 0; i < 20; i++)
	{
		if (turnT == 3)
		{
			/*if (i == 20)
				break;*/

			x = i*i*i;
			printf("%s %d\n", st, x);

			turnT += 1;
		}
		Sleep(10);
	}
	return 0;
}
int main()
{
	DWORD doThreadId;
	HANDLE t1 = CreateThread(NULL, 0, myFunc, (LPVOID)"Thread I", 0, &doThreadId);
	HANDLE t2 = CreateThread(NULL, 0, myFunc2, (LPVOID)"Thread II", 0, &doThreadId);
	HANDLE t3 = CreateThread(NULL, 0, myFunc3, (LPVOID)"Thread III", 0, &doThreadId);
	HANDLE t4 = CreateThread(NULL, 0, myFunc4, (LPVOID)"Thread IV", 0, &doThreadId);
	HANDLE t6 = CreateThread(NULL, 0, myFunc6, (LPVOID)"Thread VI", 0, &doThreadId);
	HANDLE t8 = CreateThread(NULL, 0, myFunc8, (LPVOID)"Thread VIII", 0, &doThreadId);

	system("PAUSE");
}

