#include "str.h"
#include <string.h>

UString::UString(const char* string)
{
	this->string = new str();

	this->string->len = strlen((const char *)string);
	this->string->string = new char[this->string->len + 1];
	this->string->refs = 1;
	memcpy(this->string->string, string, this->string->len+1);
}

UString::UString(const UString& original)
{
	string = original.string;
	string->refs++;
}


UString::UString()
{
	string = new str();
	string->len = 0;
	string->string = new char[1];
	string->string[0] = 0;
	string->refs = 1;
}

UString::~UString()
{
	if (string->refs == 1)
	{
		delete[]string->string;
		delete string;
	}
}

void UString::Cmprs()
{
	if (string->refs == 1)
	{
		string->len = strlen((const char*)string->string);
		char* tmp = new char[string->len + 1];
		memcpy(tmp, string->string, string->len+1);
		delete[]string->string;
		string->string = tmp;
	}
	else
	{
		str* tmp_st = new str();
		tmp_st->len = strlen((const char*)string->string);
		tmp_st->string = new char[tmp_st->len + 1];
		memcpy(tmp_st->string, string->string, tmp_st->len + 1);
		string->refs--;
		tmp_st->refs = 1;
		string = tmp_st;
	}
}

UString& UString::operator=(const char* st)
{
	if (string->refs == 1)
	{
		string->len = strlen((const char*)st);
		char* str_n = new char[string->len + 1];
		memcpy(str_n, st, string->len + 1);
		delete[]string->string;
		string->string = str_n;
	}
	else
	{
		str* tmp_st = new str();
		tmp_st->len = strlen((const char*)st);

		tmp_st->string = new char[tmp_st->len + 1];
		memcpy(tmp_st->string, st, tmp_st->len + 1);
		string->refs--;
		tmp_st->refs = 1;
		string = tmp_st;
	}
	return *this;
}

void UString::SetLen(unsigned long long i)
{
	if (string->refs == 1)
	{
		char* nstr = new char[i + 1];
		memset(nstr, 0, i + 1);
		size_t temp = (i > string->len ? string->len : i);
		memcpy(nstr, string->string, temp);
		nstr[temp] = 0;
		delete[]string->string;
		string->string = nstr;
		string->len = i;
	}
	else
	{
		str* tmp_st = new str();
		tmp_st->string = new char[i + 1];
		tmp_st->len = i;
		memset(tmp_st->string, 0, i + 1);
		size_t temp = (i > string->len ? string->len : i);
		memcpy(tmp_st->string, string->string, temp);
		tmp_st->refs = 1;
		string->refs--;
		string = tmp_st;
	}
}

char* UString::Str()
{
	return string->string;
}

unsigned long long UString::Len()
{
	return string->len;
}
