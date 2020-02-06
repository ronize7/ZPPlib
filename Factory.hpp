#pragma once
#include <memory>

template <typename T, typename ... Args>
class IFactory
{
public:
	virtual std::unique_ptr<T> create(Args&& ... args) = 0;
};

template <typename T, typename ... Args>
class SimpleFactory : public IFactory<T, Args...>
{
public:
	std::unique_ptr<T> create(Args&& ... args) override
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
};