#pragma once

#include "filedefs.h"
#include "str.h"

class Files
{
	friend class Core;
public:
	file_t Open(int file_mode, int file_openning_attr, UString path);
	bool Close(file_t);
	bool WriteToEnd(file_t, void* data, unsigned long long size);
	bool RemoveRegion(file_t, unsigned long long start, unsigned long long end);
	bool Write(file_t, unsigned long long pos, void* data, long long size);
	bool Read(file_t, char* buffer, unsigned long long pos, unsigned long long bytes);
	bool Delete(UString);
	bool Move(UString from, UString dest);
	bool Copy(UString origin_file, UString copy);
	bool PathExist(UString file);
	bool CreateDir(UString name);
	bool RemoveFile(UString file);
	UString GetAppDir();
	UString GetUserHomeDir();
	unsigned long long FileSize(file_t);
	unsigned long long FileSize(UString path);
private:
	bool Init();
	bool CleanUp();
};


extern Files* files;