#include "files.h"

#include "List.h"


#include "debugging/log.h"

#ifdef _WIN32

#include <Windows.h>

struct file
{
    file() {
        handle = nullptr;
        fmode = 0;
        fomode = 0;
    }
    HANDLE handle;
    UString path;
    int fmode;
    int fomode;
};

List<file*>* opennedFiles;

wchar_t* convert_to_wstring(const char* str)
{
    int str_len = (int)strlen(str);
    int num_chars = MultiByteToWideChar(CP_UTF8, 0, str, str_len, NULL, 0);
    wchar_t* wstrTo = (wchar_t*)malloc((num_chars + 1) * sizeof(wchar_t));
    if (wstrTo)
    {
        MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstrTo, num_chars);
        wstrTo[num_chars] = L'\0';
    }
    return wstrTo;
}

char* convert_from_wstring(const wchar_t* wstr)
{
    int wstr_len = (int)wcslen(wstr);
    int num_chars = WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, NULL, 0, NULL, NULL);
    char* strTo = (char*)malloc((num_chars + 1) * sizeof(char));
    if (strTo)
    {
        WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, strTo, num_chars, NULL, NULL);
        strTo[num_chars] = '\0';
    }
    return strTo;
}

file_t Files::Open(int mode, int omode, UString path)
{
    wchar_t* file_name = convert_to_wstring(path.Str());
    DWORD Access = 0;
    if (mode & write)
        Access = Access | GENERIC_WRITE;
    if (mode & read)
        Access = Access | GENERIC_READ;
    if (!Access)
        return nullptr;
    DWORD crt_disp = 0;
    switch (omode)
    {
    case open_exist:
        crt_disp = OPEN_EXISTING;
        break;
    case always_open:
        crt_disp = OPEN_ALWAYS;
        break;
    case open_new:
        crt_disp = CREATE_NEW;
        break;
    default:
        return nullptr;
        break;
    }
    HANDLE f = CreateFileW(file_name, Access, FILE_SHARE_READ, NULL, crt_disp, NULL, NULL);
    if (!f)
        return nullptr;
    file* res = new file;
    res->fmode = mode;
    res->fomode = omode;
    res->handle = f;
    res->path = path;
    delete[]file_name;
    return res;
}

bool Files::Close(file_t)
{
    return false;
}

bool Files::WriteToEnd(file_t f, void* data, unsigned long long size)
{
    if (!f)
        return false;
    DWORD fend2;
    DWORD fend = GetFileSize(((file*)f)->handle, &fend2);
    DWORD fsize = fend | fend2;
    SetFilePointer(((file*)f)->handle, NULL, NULL, FILE_END);
    return WriteFile(((file*)f)->handle, data, size,&fsize, nullptr);;
}

bool Files::RemoveRegion(file_t, unsigned long long start, unsigned long long end)
{
    return false;
}

bool Files::Write(file_t, unsigned long long pos, void* data, long long size)
{
    return false;
}

bool Files::Read(file_t f,char* buffer, unsigned long long pos, unsigned long long bytes)
{
    SetFilePointer(((file*)f)->handle, pos, NULL, FILE_BEGIN);
    bool res = ReadFile(((file*)f)->handle, buffer, bytes, NULL, NULL);
    Log(lDebug,"%d",GetLastError());
    return res;
}

bool Files::Delete(UString)
{
    return false;
}

bool Files::Move(UString from, UString dest)
{
    return false;
}

bool Files::Copy(UString origin_file, UString copy)
{
    return false;
}

bool Files::PathExist(UString file)
{
    wchar_t* name = convert_to_wstring(file.Str());
    DWORD dwAttrib = GetFileAttributesW(name);

    bool res = dwAttrib != INVALID_FILE_ATTRIBUTES;
    free(name);
    return res;
}

bool Files::CreateDir(UString name)
{
    wchar_t* wname = convert_to_wstring(name.Str());
    bool res = CreateDirectoryW(wname,NULL);
    free(wname);
    return res;
}

bool Files::RemoveFile(UString file)
{
    wchar_t* wname = convert_to_wstring(file.Str());
    bool res = DeleteFileW(wname);
    free(wname);
    return res;
}

UString Files::GetAppDir()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    return UString(convert_from_wstring(buffer));
}

unsigned long long Files::FileSize(file_t f)
{
    DWORD start, end;
    start = GetFileSize(((file*)f)->handle,&end);
    return unsigned long long(start) | ((unsigned long long)end << 32);
}

unsigned long long Files::FileSize(UString path)
{
    return 0;
}

bool Files::Init()
{
    opennedFiles = new List<file*>();

    return true;
}

bool Files::CleanUp()
{
    return false;
}
#endif