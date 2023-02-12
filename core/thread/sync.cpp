#include "sync.h"

#ifdef _WIN32

#include <Windows.h>

bool Semaphore::Init(unsigned int init_count, unsigned int max_count)
{
    handle = CreateSemaphore(NULL, init_count, max_count, NULL);
    if (handle)
        return true;
    count = init_count;
    return false;
}

bool Semaphore::Destroy()
{
    CloseHandle(handle);
    return true;
}

unsigned int Semaphore::Count()
{
    return count;
}

void Semaphore::Enter()
{
    WaitForSingleObject(handle, INFINITE);
    count--;
}

void Semaphore::Enter(unsigned int millisec)
{
    WaitForSingleObject(handle, millisec);
    count--;
}

void Semaphore::Leave()
{
    count++;
    ReleaseSemaphore(handle, 1, NULL);
}

bool Mutex::Init(bool init_state)
{
    handle = CreateMutex(NULL,init_state,NULL);
    if (handle)
        return true;
    lock = init_state;
    return false;
}

bool Mutex::Destroy()
{
    CloseHandle(handle);
    return true;
}

unsigned int Mutex::Locked()
{
    return lock;
}

void Mutex::Enter()
{
    WaitForSingleObject(handle, INFINITE);
    lock = true;
}

void Mutex::Enter(unsigned int millisec)
{
    WaitForSingleObject(handle, millisec);
    lock = true;
}

void Mutex::Leave()
{
    lock = false;
    ReleaseMutex(handle);
}

void Sleep(int time_inMicroSec)
{
    HANDLE timer;
    LARGE_INTEGER ft;
    ft.QuadPart = -(10 * time_inMicroSec); // Convert to 100 nanosecond interval, negative value indicates relative time
    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (timer)
    {
        SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
        WaitForSingleObject(timer, INFINITE);
        CloseHandle(timer);
    }
}
#elif __linux
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


void Sleep(int time_inMicroSec)
{
    usleep(time_inMicroSec);
}
#endif 

void Block::Enter()
{
    while (lock)
    {
        Sleep(0);
    }
}
