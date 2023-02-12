#pragma once
#include <string.h>
#include <stdlib.h>

template <typename T>
class List
{
	struct container
	{
		T* dt;
		size_t refs;
		size_t size;
		size_t bytes;
	};
public:
	List(size_t size = 0)
	{
		data = (container*)malloc(sizeof(container));
		data->bytes = size * sizeof(T);
		if (size)
		{
			data->dt = (T*)malloc(data->bytes);
			memset(data->dt, 0, data->bytes);
		}
		else
			data->dt = nullptr;
		data->refs = 1;
		data->size = size;
	}

	inline void Add(T val)
	{
		Realloc(data->size + 1);
		data->dt[data->size] = val;
		data->size++;
	}
	inline void Add(T* val, unsigned long long i)
	{
		Realloc(data->size + i);
		memcpy(data->dt+ data->size *sizeof(T), val, i * sizeof(T));
	}

	inline unsigned long long Size()
	{
		return data->size;
	}

	inline T* Data()
	{
		Refs();
		return data->dt;
	}

	inline void Remove(unsigned long long i)
	{
		Refs();
		memcpy(data->dt + sizeof(T) * i, data->dt + sizeof(T) * i + 1, data->bytes - sizeof(T) * i + 1);
		data->size--;
		Realloc(data->size);
	}
	inline long long Find(T val)
	{
		for (size_t i = 0; i < data->size; i++)
		{
			if (data->dt[i] == val)
			{
				return i;
			}
		}
		return -1;
	}
	~List()
	{
		if (data->refs <= 1)
		{
			free(data->dt);
			free(data);
			return;
		} else
		{
			data->refs--;
		}
	}
	T &operator [] (size_t i)
	{
		return data->dt[i];
	}
	T El(size_t i)
	{
		return data->dt[i];
	}
	inline void Refs()
	{
		if (data->refs <= 1)
			return;
		container* cnt = (container*)malloc(sizeof(container));
		cnt->bytes = data->bytes;
		cnt->refs = 1;
		cnt->size = data->size;
		cnt->dt = (T*)malloc(data->bytes);
		memcpy(cnt->dt, data->dt, data->bytes);
		data->refs--;
		data = cnt;
	}
	inline void Resize(int i)
	{
		Realloc(i);
		data->size = i;
	}

private:

	inline void Realloc(unsigned long long i)
	{
		Refs();
		size_t bytes = i * sizeof(T);
		T* temp = (T*)malloc(bytes);
		if (data->bytes > 0)
		{
			memcpy(temp, data->dt, data->bytes);
			free(data->dt);
		}
		data->dt = temp;
		data->bytes = bytes;
	}
	container* data;

};