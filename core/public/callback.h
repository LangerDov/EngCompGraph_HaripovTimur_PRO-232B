#pragma once

template <typename T>
struct callback_t
{
	callback_t()
	{
		func = nullptr;
		data = nullptr;
	}
	T(*func)(void*);
	void* data;
};