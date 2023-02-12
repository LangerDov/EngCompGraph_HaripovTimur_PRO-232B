#pragma once

class Semaphore
{
public:
	bool Init(unsigned int init_count, unsigned int max_count);
	bool Destroy();
	unsigned int Count();
	void Enter();
	void Enter(unsigned int millisec);
	void Leave();

private:
	void* handle;
	unsigned int count;
};

class Mutex
{
public:
	bool Init(bool locked);
	bool Destroy();
	unsigned int Locked();
	void Enter();
	void Enter(unsigned int millisec);
	void Leave();

private:
	void* handle;
	bool lock;
};

class Block
{
public:
	bool lock;
	void Enter();
private:
};

extern void Sleep(int time_inMicroSec);