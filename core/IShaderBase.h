#ifndef _ISHADERBASE_H
#define _ISHADERBASE_H

class IShaderBase
{
public:
	virtual void Init(const char *) = 0;
	virtual void Shutdown() = 0;

	
};

#endif