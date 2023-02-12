#ifdef _WIN32
#include <Windows.h>

#elif __linux
#include <pthread.h>
#include <unistd.h>
#endif
#include "asyncthread.h"

CAsyncThread::CAsyncThread()
{
}
CAsyncThread::~CAsyncThread() 
{
}

#ifdef _WIN32

DWORD WINAPI ThreadStart(void *pParam)
{
    threadinfo_t* pThreadInfo = (threadinfo_t*)pParam;
    if (pThreadInfo)
        pThreadInfo->pFunc(pThreadInfo->pData);
    delete pThreadInfo;
	return 0;
}

void CAsyncThread::Start(threadinfo_t *pThreadInfo)
{
    CreateThread(0, 0, ThreadStart, pThreadInfo, 0, 0);
}

void CAsyncThread::Pause()
{

}

void CAsyncThread::Resume()
{

}


#elif __linux
void *ThreadStart(void* param)
{
    threadinfo_t *pInfo = (threadinfo_t*)param;
    if (pInfo)
        pInfo->pFunc(pInfo->pData);
    return nullptr;
}

void CAsyncThread::Start(threadinfo_t *pInfo)
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, ThreadStart, (void*)pInfo);
    pthread_detach(tid);
}
#endif