#pragma once

#ifdef _WIN32

#define PATH_SEPR "\\"

#elif __unix

#define PATH_SEP '\/'
#endif // _WIN32

#define CONFIGS_FOLDER "configs"

#define MAIN_CFG_NAME "main.xml"

enum file_mode
{
	write = 1 << 0,
	read = 1 << 1,
};

enum file_openning_mode
{
	// will open file if it exist
	open_exist,
	// if file exist, will be open existing file, else will create new file
	always_open,
	// always create new file, if was exist, will delete existing file
	open_new,
};

typedef void* file_t;