#include "DllInjector.hpp"
#include "AutoCloseHandle.hpp"
#include <iostream>

typedef HMODULE (*LoadLibraryW_sig)(
	LPCWSTR lpLibFileName
);

DllInjector::DllInjector(const Process& process, const std::wstring& dll_path) :
	m_process(process),
	m_dll_path(dll_path)
{
}

void DllInjector::inject()
{
	AutoCloseHandle process = OpenProcess(PROCESS_QUERY_INFORMATION  | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, false, m_process.get_process_id());
	if (nullptr == process.get())
	{
		throw;
	}

	PVOID remote_mem = VirtualAllocEx(process.get(), nullptr, m_dll_path.size(), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (nullptr == remote_mem)
	{
		throw;
	}
	
	SIZE_T size_written = 0;
	if (!WriteProcessMemory(process.get(), remote_mem, m_dll_path.c_str(), m_dll_path.size(), &size_written))
	{
		throw;
	}
	if (0 == size_written)
	{
		throw;
	}

	HMODULE k32 = GetModuleHandleW(L"kernel32.dll");
	if (nullptr == k32)
	{
		throw;
	}

	LoadLibraryW_sig ll = (LoadLibraryW_sig)GetProcAddress(k32, "LoadLibraryW");
	if (nullptr == k32)
	{
		throw;
	}

	AutoCloseHandle thread = CreateRemoteThread(process.get(), nullptr, 0, (PTHREAD_START_ROUTINE)ll, remote_mem, 0, nullptr);
	if (NULL == thread.get())
	{
		std::cout << "CreateRemoteThread Failed" << std::endl;
		throw;
	}

	WaitForSingleObject(thread.get(), INFINITE);
}
