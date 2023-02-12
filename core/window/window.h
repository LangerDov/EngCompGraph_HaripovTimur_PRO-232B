#pragma once
#include "thread/asyncthread.h"
#include "thread/sync.h"
#include "windowdefs.h"
#include "callback.h"
#include "graphics/render/renderinterface.h"
#include "str.h"

void InitWindowSubsys();
bool WindowSubsysIsWork();
void DestroyWindowSubsys();

struct crsr_pos_callback_data_t
{
	double x;
	double y;
	void* data;
};

struct resize_callback_data_t
{
	double width;
	double height;
	void* data;
};

class Window
{
	friend void CloseWinCallback(void* HWIN);
	friend void WindowThread(void*);
	friend void KeyCallback(void* HWIN, int key, int scancode, int action, int mods);
	friend void CursorPosCallback(void* HWIN, double xpos, double ypos);
	friend void SizeCallback(void* window, int width, int height);
public:
	Window();
	~Window();
	void Create();
	bool Open(window_open_attr);
	bool Close();
	void Destroy();
	bool SetTitle(UString title);
	//void SetRoot(ViewPort*);
	void SetOnTryClose(callback_t<bool>callback);
	void SetOnCursorMove(callback_t<void>callback);
	void SetOnWindowResize(callback_t<void>callback);
	void* GetHWIN();
	IRenderInterface* GetRenderInterface();
private:
	//ViewPort* rootgrhpcmp;
	window_open_attr opennig_attr;
	threadinfo_t* thrd_info;
	CAsyncThread* window_thread;
	Block* block;
	Block* RenderBlock;
	UString title;
	callback_t<bool>on_tryclose;
	callback_t<void>on_crsr_move;
	callback_t<void>on_chngsize;
	callback_t<void>on_key_press;
	void* HWIN;
	int width;
	int height;
	int x;
	int y;
	int monitor;
	IRenderInterface* pRender;
};
