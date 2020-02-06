#pragma once
#include <string>
#include <iostream>

class Logger
{
public:
	void log(const wchar_t* format)
	{
		std::wcout << format;
	}

	template<typename T, typename ... Args>
	void log(const wchar_t* format, T&& value, Args&& ... args)
	{
		if (format[0] == L'%')
		{
			std::wcout << value;
			log(format + 1, std::forward<Args>(args)...);
		}
		else
		{
			std::wcout << format[0];
			log(format + 1, std::forward<T>(value), std::forward<Args>(args)...);
		}
	}
};
