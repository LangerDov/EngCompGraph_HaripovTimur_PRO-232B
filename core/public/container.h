#pragma once
#include <stdlib.h>

template <typename T>
class Container
{
	struct cntnr_t
	{
		T* data;
		size_t size;
		size_t refs;
	};
public:
	Container()
	{
		data = (cntnr_t*)malloc( sizeof(cntnr_t));
		data->data = nullptr;
		data->size = 0;
		data->refs = 1;
	}
	~Container()
	{
		if (data)
		{
			if (data->refs <= 1)
			{
				free(data);
				return;
			}
			data->refs--;
		}
	}
	Container(const Container& cont)
	{
		if (cont.data)
		{
			data = cont.data;
			data->refs++;
		}
	}
	bool MakeNewInst()
	{
		if (data->refs == 1)
			return false;
		cntnr_t* newinst = malloc(size);
	}

	const T& operator [] (size_t i)
	{
		return data->dt[i];
	}
protected:

private:
	cntnr_t* data;
};
