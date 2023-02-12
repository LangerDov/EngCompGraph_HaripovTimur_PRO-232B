#pragma warning(disable:4244)

#include "core.h"
#include "debugging/log.h"
#include "thread/asyncthread.h"
#include "thread/sync.h"

#include "files/files.h"

#include "List.h"
#include <intrin.h>

#include "window/window.h"

#include "GLFW/glfw3.h"

struct tickProc
{
	void(*func)(void*);
	void* data;
};

bool mainLoop = false;

Files* files;

List<tickProc*>* TickProcess;
Mutex* TkPMutex;
CAsyncThread* TkPThread;


void(*logprint)(UString) = nullptr;

CAsyncThread* SlThread;

file_t log_file = nullptr;


void TickThread(void* data);
void SleepThread(void* data);

int isAvxSupportedByCpu() {
	int cpuInfo[4];
	__cpuid(cpuInfo, 0);
	if (cpuInfo[0] != 0) {
		__cpuid(cpuInfo, 1);
		return cpuInfo[3] & 0x10000000; // Возвращаем ноль, если 28-ой бит в ecx сброшен
	}
	else {
		return 0; // Процессор не поддерживает получение информации о поддерживаемых наборах инструкций
	}
}

Core::Core()
{
	mainLoop = false;
	if (!isAvxSupportedByCpu())
	{
		Log(lFatal, "AVX NOT SUPPORTED");
	}
	else
	{
		Log(lInfo, "AVX supported");
	}
	files = new Files();
	files->Init();
	if (!files->PathExist("logs"))
		files->CreateDir("logs");
	files->RemoveFile("logs/last.log");
	log_file = files->Open(write, open_new, "logs/last.log");
	
	glfwInit();

	TkPMutex = new Mutex;
	TkPMutex->Init(false);
	TickProcess = new List<tickProc*>;
	TkPThread = new CAsyncThread;
	threadinfo_t* TkPThreadInfo = new threadinfo_t();
	TkPThreadInfo->pFunc = TickThread;
	TkPThread->Start(TkPThreadInfo);
	Log(lDebug, "Tick system loaded");
	SlThread = new CAsyncThread;
	threadinfo_t* slThreadInfo = new threadinfo_t();
	slThreadInfo->pFunc = SleepThread;
	SlThread->Start(slThreadInfo);
	Log(lDebug, u8"Sleep env thread loaded");
	Log(lInfo, u8"Core object loaded!");
	mainLoop = true;
}

void TickThread(void* data)
{
	unsigned long long start, end,diff;
	int size = 0;
	tickProc* tKP;
}

void SleepThread(void* data)
{
}

void Core::Run()
{
	Window win;
	win.Create();
	win.Open(window_open_attr());
	while (mainLoop)
	{
		Sleep(1);
	}
	files->CleanUp();
}

tickProc_t Core::CreateTickProc(void(*func)(void*), void* data)
{
	tickProc* proc = new tickProc;
	proc->data = data;
	proc->func = func;
	TkPMutex->Enter();
	TickProcess->Add(proc);
	TkPMutex->Leave();
	return proc;
}

bool Core::RemoveTickProc(tickProc_t proc)
{
	int i = TickProcess->Find((tickProc*)proc);
	if (i == -1)
		return false;
	TkPMutex->Enter();
	TickProcess->Remove(i);
	TkPMutex->Leave();
	return true;
}

void Core::ShutDown()
{
	mainLoop = false;
}
