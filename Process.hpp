#pragma once

#include "Common.hpp"
#include <tlhelp32.h>

class Process
{
public:
	Process(const PROCESSENTRY32W& process_data);
	virtual ~Process() = default;
	
	Process(const Process&) = default;
	Process(Process&&) = default;

	std::wstring get_process_name() { return m_process_data.szExeFile; };
	uint32_t get_process_id() { return m_process_data.th32ProcessID; };

private:
	const PROCESSENTRY32W m_process_data;
};
