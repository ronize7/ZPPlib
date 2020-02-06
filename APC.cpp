#include <Windows.h>
#include <iostream>
#include "APC.hpp"

void NTAPI APC::_s_apc(ULONG_PTR Parameter)
{
	MessageBoxW(0, 0, 0, 0);
}

void APC::s_run()
{
	if (!QueueUserAPC((PAPCFUNC)_s_apc, GetCurrentThread(), 0))
	{
		std::cout << GetLastError() << std::endl;
		return;
	}

	SleepEx(1000, true);
}