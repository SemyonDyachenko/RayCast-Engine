#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


#include "../../Core/Window.h"



class glWindow : public Window
{
public:
	glWindow(WindowProps & props);

	virtual ~glWindow();

	void OnUpdate() override;

	unsigned int GetWidth() const override;
	unsigned int GetHeight() const  override;

	void PollEvent() override;
	void SwapBuffers() override;

	void EnableVSync(bool enabled) override;
	bool IsVSync() override;

	void SetSize(int width,int height) override;

	void Clear() override;

	void Close() override;

	void SetFullscreen() override;

	bool Closed() const override;

	virtual GLFWwindow* GetNativeWindow() const override;
private:
	GLFWwindow* m_Window;

	std::string m_Title;
	unsigned int m_Width, m_Height;
	bool VSync;
	bool Fullscreen;
};

#endif