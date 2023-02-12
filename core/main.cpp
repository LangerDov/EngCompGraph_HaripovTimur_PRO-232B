#include "core.h"

#ifdef _WIN32
extern "C" __declspec(dllexport) int NvOptimusEnablement = 1;
#endif

int main()
{
	Core *coreObj = new Core();
	coreObj->Run();
	delete coreObj;
	return 0;
}

#ifdef _WIN32
int WinMain()
{
	return main();
}
#endif