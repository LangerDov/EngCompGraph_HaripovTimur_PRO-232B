#pragma once
#include "locale.h"
#include "str.h"

class MLString
{
public:
	UString& operator [](locale_t i)
	{
		return  strings[i];
	}
private:
	UString strings[max];
};