#pragma once

#include "Process.hpp"
#include <vector>

class ProcessList
{
public:
	static std::vector<Process> s_get_processs_list();
};
