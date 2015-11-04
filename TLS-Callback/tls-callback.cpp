// @source: http://www.unknowncheats.me/forum/c-and-c/84146-tls-callback-tutorial.html
#include "windows.h"
#include <stdio.h>

void NTAPI __stdcall TLSCallbacks(PVOID DllHandle, DWORD dwReason, PVOID Reserved);
//linker spec
#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif
EXTERN_C
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
const
#else
#pragma data_seg (".CRT$XLB")
#endif
//end linker

//tls import
PIMAGE_TLS_CALLBACK _tls_callback = TLSCallbacks;
#pragma data_seg ()
#pragma const_seg ()
//end 
// tls declaration
#include <iostream>
void NTAPI __stdcall TLSCallbacks(PVOID DllHandle, DWORD dwReason, PVOID Reserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH: 
		std::cout << "Process attach" << std::endl;
		break;
	case DLL_PROCESS_DETACH: 
		std::cout << "Process dettach" << std::endl;
		break;
	case DLL_THREAD_ATTACH: 
		std::cout << "Thread attach" << std::endl;
		break;
	case DLL_THREAD_DETACH: 
		std::cout << "Thread dettach" << std::endl;
		break;
	}
}

// end declaration

#include "process.h"
thread_local long rage = 0L;

void threadFunction(void*)
{
	rage = std::rand();
	printf("Rage is: %d\n", rage);
	while (true) Sleep(INFINITE);
}

int main(int argc, char* argv[])
{
	for (auto i = 0; i < 1; i++)
	{
		auto retVal = HANDLE(_beginthread(threadFunction, 0, nullptr));
		printf("Thread id: %d\n", GetThreadId(retVal));
	}
	system("pause");
}

