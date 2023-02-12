#ifndef _CORE_H
#define _CORE_H

#include "str.h"

typedef void* tickProc_t;


class Core
{
public:
	Core();
	void Run();
	static tickProc_t CreateTickProc(void(*func)(void*), void* data);
	static bool RemoveTickProc(tickProc_t);
	static void ShutDown();
private:

};

#endif