#pragma once
#include "Common.hpp"

class AutoCloseHandle
{
public:
	AutoCloseHandle(HANDLE handle);
	virtual ~AutoCloseHandle();

	AutoCloseHandle(const AutoCloseHandle&) = delete;

	AutoCloseHandle(AutoCloseHandle&&) = default;

	HANDLE get() { return m_handle; }

private:
	HANDLE m_handle;
};
