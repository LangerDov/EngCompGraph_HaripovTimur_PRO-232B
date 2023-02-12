#pragma once
#include "List.h"
typedef void* window_t;
typedef void* bind_handler;
typedef void* HWIN;




struct window_attr
{
	bool decorated = true;
	bool resizable = true;
	bool floating = false;
	bool iconfied = false;
	bool focus_on_show = true;
	bool fullscreen = false;
};

struct window_open_attr: window_attr
{
	bool focused = false;
	bool visible = true;
	bool maximized = false;
	bool centered_cursor = false;
	bool transparent_framebuffer = false;
	bool hovered = false;
};