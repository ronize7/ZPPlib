#include "Process.hpp"

Process::Process(const PROCESSENTRY32W& process_data) :
	m_process_data(process_data)
{}
