#pragma once

class UString
{
	struct str
	{
		char* string = nullptr;
		size_t refs = 0;
		size_t len = 0;
	};
public:
	UString(const char*);
	UString(const UString&);
	UString();
	~UString();
	void Cmprs();
	UString& operator=(const char* string);
	void SetLen(unsigned long long);
	char* Str();
	unsigned long long Len();
private:
	str* string;
};