#include "AutoCloseHandle.hpp"

AutoCloseHandle::AutoCloseHandle(HANDLE handle) :
	m_handle(handle)
{
}

AutoCloseHandle::~AutoCloseHandle()
{
	try
	{
		CloseHandle(m_handle);
	}
	catch(...)
	{ }
}
