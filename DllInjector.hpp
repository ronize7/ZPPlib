#include "Common.hpp"
#include "Process.hpp"

class DllInjector
{
public:
	DllInjector(const Process& process, const std::wstring& dll_path);

	void inject();

private:
	Process m_process;
	const std::wstring m_dll_path;
};