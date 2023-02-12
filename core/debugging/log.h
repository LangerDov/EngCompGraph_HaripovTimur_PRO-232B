#pragma once
#include "str.h"
enum logtype
{
	lErr,
	lFatal,
	lWarn,
	lDebug,
	lInfo,
	lScript,
	lNone,
};

void Log(logtype tp, UString format, ...);
