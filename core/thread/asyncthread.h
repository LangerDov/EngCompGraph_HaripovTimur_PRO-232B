#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#pragma once

typedef void* semaphore_t;
typedef void* mutex_t;
typedef void* critical_section_t;

struct threadinfo_t
{
	threadinfo_t() { pFunc = nullptr; pData = nullptr; }
	void(*pFunc)(void *);
	void* pData;
};

class CAsyncThread
{
public:
	CAsyncThread();
	~CAsyncThread();

	// thread should free threadinfo
	void Start(threadinfo_t *pThreadInfo);
	void Pause();
	void Resume();
};


#endif