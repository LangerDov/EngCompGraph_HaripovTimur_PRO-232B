#ifndef _RENDERINTERFACE_H
#define _RENDERINTERFACE_H

typedef void *renderdata_t;
typedef void (*msgcallback_t)(const char *pMsg);

enum buffermemory_t
{
	memory_ram = 1,
	memory_gpu
};

class IRenderInterface
{
public:
	/// <summary>
	/// Initializes pukan interface
	/// </summary>
	/// <param name="pWindow">Pointer to GLFW window</param>
	/// <returns>True if succeded, false if failed</returns>
	virtual bool Init(void *pWindow, msgcallback_t pCallbackFunc = nullptr) = 0;
	virtual void Shutdown() = 0;

	virtual void SetViewport(int width, int height) = 0;

	virtual void BeginTransfer() = 0;
	
	virtual renderdata_t LoadMemoryToRam(void* pData, size_t ulSize) = 0;
	// if you store data in ram, then you may not to call begin end transfer
	virtual renderdata_t LoadMemoryToGpu(void* pData, size_t ulSize) = 0;

	virtual void EndTransfer(bool bWait = true) = 0;

	virtual void FreeRamMemory(renderdata_t pData) = 0;
	virtual void FreeGpuMemory(renderdata_t pData) = 0;

	// RENDER COMMAND QUEUE

	// Begin recording command queue
	virtual void StartQueue() = 0;

	// use shaders to draw meshes
	virtual void Draw(renderdata_t pBuffer, unsigned int vertCount) = 0;
	virtual void DrawIndexed(renderdata_t pVertexBuffer, size_t indexOffset, unsigned int idxCount) = 0;

	// End recording command queue and present rendered to screen
	virtual void EndQueue() = 0;
	virtual void WaitForDevice() = 0;
};

extern IRenderInterface* CreateVulkanInterface();

#endif