#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "files/files.h"
extern void(*logprint)(UString);
extern file_t log_file;


void Log(logtype tp, UString text, ...)
{
	UString msgtype;
	UString szBuf;
	szBuf.SetLen(1024);
	switch (tp)
	{
	case lErr:
		msgtype = "ERROR";
		break;
	case lFatal:
		msgtype = "FATAL ERROR:";
		break;
	case lWarn:
		msgtype = "WARNING:";
		break;
#ifdef _DEBUG
	case lDebug:
		msgtype = "DEBUG:";
		break;
#endif // _DEBUG
	case lInfo:
		msgtype = "INFO:";
		break;
	case lScript:
		msgtype = "SCRIPT:";
		break;
	}
	va_list args;
	va_start(args, text);
	vsprintf(szBuf.Str(), text.Str(), args);
	va_end(args);
	UString res;
	res.SetLen(2048);
	sprintf(res.Str(), "%s %s\n", msgtype.Str(), szBuf.Str());

	printf(u8"%s", res.Str());
	res.Cmprs();
	files->WriteToEnd(log_file, res.Str(), res.Len());
#if(defined _WIN32 && defined _DEBUG)
	OutputDebugString(res.Str());
#endif
	if (logprint)
		logprint(szBuf);
}
