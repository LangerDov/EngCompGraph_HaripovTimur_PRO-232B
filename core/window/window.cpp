#include "window.h"
#include <GLFW/glfw3.h>
#include "debugging/log.h"
#include "matvec.h"

int glfw_state = GLFW_FALSE;

void CloseWinCallback(void* HWIN)
{
    Window* win = (Window*)glfwGetWindowUserPointer((GLFWwindow*)HWIN);
    if (!win)
        return;
    if (!win->on_tryclose.func)
        return;
    if (win->on_tryclose.func(win->on_tryclose.data))
        glfwSetWindowShouldClose((GLFWwindow*)HWIN, GLFW_TRUE);
    else
        glfwSetWindowShouldClose((GLFWwindow*)HWIN, GLFW_FALSE);
}
void KeyCallback(void* HWIN, int key, int scancode, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer((GLFWwindow*)HWIN);
    if (!win)
        return;
}

void SizeCallback(void* window, int width, int height)
{
    Window* win = (Window*)glfwGetWindowUserPointer((GLFWwindow*)window);
    if (!win)
        return;
    if (win->on_chngsize.func)
    {
        resize_callback_data_t data;
        data.data = win->on_chngsize.data;
        data.height = height;
        data.width = width;
        win->on_chngsize.func(&data);
    }
    win->GetRenderInterface()->WaitForDevice();
    win->GetRenderInterface()->SetViewport(width, height);
}

static void CursorPosCallback(void* HWIN, double xpos, double ypos)
{
    Window* win = (Window*)glfwGetWindowUserPointer((GLFWwindow*)HWIN);
    if (!win)
        return;
    if (!win->on_crsr_move.func)
        return;
    static crsr_pos_callback_data_t arg;
    arg.data = win->on_tryclose.data;
    arg.x = xpos;
    arg.y = ypos;
    win->on_crsr_move.func(&arg);
    //Log(lDebug, "x %f  y %f %d", xpos, ypos, win);
}

void vulkan_debug(const char* pMessage)
{
    Log(lDebug, pMessage);
}

void WindowThread(void* data)
{
    Window* parent = (Window*)data;
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    void* monitor = NULL;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_FALSE);
    if (parent->opennig_attr.resizable)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if (parent->opennig_attr.decorated)
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    if (parent->opennig_attr.floating)
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
    if (parent->opennig_attr.focused)
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    if (parent->opennig_attr.focus_on_show)
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    if (parent->opennig_attr.fullscreen)
        monitor = monitors[parent->monitor];
    if (parent->opennig_attr.iconfied)
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
    if (parent->opennig_attr.maximized)
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    if (parent->opennig_attr.centered_cursor)
        glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
    if (parent->opennig_attr.transparent_framebuffer)
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    if (parent->opennig_attr.visible)
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    parent->HWIN = glfwCreateWindow(parent->width, parent->height, parent->title.Str(), (GLFWmonitor*)monitor, NULL);
    if (!parent->HWIN)
        return;
    glfwSetWindowUserPointer((GLFWwindow*)parent->HWIN, parent);
    glfwSetWindowCloseCallback((GLFWwindow*)parent->HWIN, (void (*)(GLFWwindow*))CloseWinCallback);
    glfwSetKeyCallback((GLFWwindow*)parent->HWIN, (void (*)(GLFWwindow*, int, int, int, int))KeyCallback);
    glfwSetCursorPosCallback((GLFWwindow*)parent->HWIN, (void(*)(GLFWwindow*,double,double))CursorPosCallback);
    glfwSetWindowSizeCallback((GLFWwindow*)parent->HWIN, (void(*)(GLFWwindow*, int, int))SizeCallback);
    // init (p)vulkan
    parent->pRender = CreateVulkanInterface();
    IRenderInterface* pRender = parent->pRender;

    if (!pRender->Init(parent->HWIN, vulkan_debug))
        return;

    float vertices[] = {
        0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f,
        -0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f,
        -0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f,
        0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f
    };
    uint32_t indices[] = { 0, 1, 2, 2, 0 };

    void* pTriangle = malloc(sizeof(vertices) + sizeof(indices));
    memcpy(pTriangle, vertices, sizeof(vertices));
    memcpy((void*)((size_t)pTriangle + sizeof(vertices)), indices, sizeof(indices));

    pRender->BeginTransfer();
    renderdata_t test = pRender->LoadMemoryToGpu(pTriangle, sizeof(vertices) + sizeof(indices));
    pRender->EndTransfer();

    free(pTriangle);

    //Matrix test = 
    //    Matrix::Projection(4.f / 3.f, 45.f, 0.1f, 50.f) * Matrix::Camera(Vector(0.f, 0.f, -5.f), Vector(0.f, 0.f, 0.f));

    parent->block->lock = false;
    //parent->rootgrhpcmp->InitDraw(parent->HWIN);
    while (!glfwWindowShouldClose((GLFWwindow*)parent->HWIN))
    {
        pRender->StartQueue();
        pRender->DrawIndexed(test, sizeof(vertices), 6);
        pRender->EndQueue();
        glfwPollEvents();
    }
    pRender->WaitForDevice();
    pRender->Shutdown();
    glfwDestroyWindow((GLFWwindow*)parent->HWIN);
    parent->HWIN = NULL;
}

Window::Window()
{
    width = height = 0;
    x = y = 0;

    thrd_info = nullptr;
    HWIN = nullptr;
    RenderBlock = nullptr;
    block = nullptr;
    monitor = 0;
    pRender = nullptr;
    window_thread = nullptr;
}

Window::~Window()
{
}

void Window::Create()
{
    width = 640;
    height = 480;
    x = 0;
    y = 0;
    monitor = 0;
    title = "Title";
    on_tryclose.data = nullptr;
    on_tryclose.func = nullptr;
    window_thread = new CAsyncThread;
    thrd_info = new threadinfo_t();
    thrd_info->pFunc = WindowThread;
    thrd_info->pData = this;
    block = new Block;
    block->lock = true;
}
bool Window::Open(window_open_attr attr)
{
    opennig_attr = attr;
    window_thread->Start(thrd_info);
    block->Enter();
    return true;
}

bool Window::Close()
{
    return false;
}

void Window::Destroy()
{
}

bool Window::SetTitle(UString title)
{
    if (HWIN)
        glfwSetWindowTitle((GLFWwindow*)HWIN, title.Str());
    this->title = title;
    return true;
}

//void Window::SetRoot(ViewPort* vp)
//{
//    bool lock = block->lock;
//    block->lock = true;
//    Sleep(1);
//    rootgrhpcmp = vp;
//    block->lock = lock;
//}
void Window::SetOnTryClose(callback_t<bool> callback)
{
    on_tryclose = callback;
}

void Window::SetOnCursorMove(callback_t<void>callback)
{
    on_crsr_move = callback;
}

void Window::SetOnWindowResize(callback_t<void> callback)
{
    on_chngsize = callback;
}

void* Window::GetHWIN()
{
    return HWIN;
}

IRenderInterface* Window::GetRenderInterface()
{
    return pRender;
}


void InitWindowSubsys()
{
    glfw_state = glfwInit();
}

bool WindowSubsysIsWork()
{
    return glfw_state;
}

void DestroyWindowSubsys()
{
    glfwTerminate();
    glfw_state = GLFW_FALSE;
}
