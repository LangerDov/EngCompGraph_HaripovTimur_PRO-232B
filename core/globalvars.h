#pragma once
#include "str.h"
#include "locale.h"


struct globalVars
{
	unsigned int TPS_max = 120;
	unsigned int TPS = 0;
	// in microsec
	unsigned int TPS_time = 0;
	unsigned long long tick_count = 0;
	bool work;
	UString current_dir;
	UString prj_name = u8"gayEngine";
	locale_t locale_t = en;
	struct version_t
	{
		char main = 0;
		char sub = 0;
		char build = 0;
		char sub_build = 0;
		char type = 'a';
		UString name = u8"gayEngine dev";
	};
	const version_t version;
};

extern globalVars* gVars;