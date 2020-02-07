#include "ProcessList.hpp"
#include "AutoCloseHandle.hpp"

std::vector<Process> ProcessList::s_get_processs_list()
{
	AutoCloseHandle snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == snapshot.get())
	{
		throw;
	}

	std::vector<Process> processes;

	PROCESSENTRY32W process_data = { 0 };
	process_data.dwSize = sizeof(process_data);

	if (!Process32FirstW(snapshot.get(), &process_data))
	{
		throw;
	}

	do
	{
		Process process(process_data);
		processes.push_back(process);

	} while (Process32NextW(snapshot.get(), &process_data));

	return processes;
}
