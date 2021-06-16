#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <memory>
#include <string>
#include <GLFW/glfw3.h>
#include "Event.h"
#include <functional>

struct WindowProps {
	std::string title;
	unsigned int width;
	unsigned int height;
	bool fullscreen;
	bool vsync;
};

class Window {
public:
	using EventCallbackFn = std::function<void(Event&)>;

	virtual ~Window() = default;

	virtual void OnUpdate() = 0;

	virtual void PollEvent() = 0;
	virtual void SwapBuffers() = 0;

	virtual  unsigned int GetWidth() const = 0;
	virtual  unsigned int GetHeight() const = 0;

	virtual void EnableVSync(bool enabled) = 0;
	virtual bool IsVSync() = 0;

	virtual void SetSize(int width, int height) = 0;

	virtual GLFWwindow* GetNativeWindow() const = 0;

	virtual void Clear() = 0;
	
	virtual void Close() = 0;

	virtual bool Closed() const = 0;

	virtual void SetFullscreen() = 0;

	virtual void SetEventCallback(const EventCallbackFn & callback) = 0;

	virtual	EventCallbackFn GetScrollCallBack() = 0;

	static std::unique_ptr<Window> Create(WindowProps & props);

	
};

#endif