#include "../../../stdafx.h"
#include "glWindow.h"

#include "../../Rendering/stb_image.h"

glWindow::glWindow(WindowProps& props) 
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}

    m_Width = props.width;
    m_Height = props.height;
    m_Title = props.title;
    VSync = props.vsync;
    Fullscreen = props.fullscreen;

    glfwWindowHint(GLFW_SAMPLES, 4);
	
	m_Window = glfwCreateWindow(m_Width,m_Height,m_Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_Window);

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWimage icons[1];
    icons[0].pixels = stbi_load("resources/icons/icon.png", &icons[0].width, &icons[0].height, 0, 0);
    glfwSetWindowIcon(m_Window, 1, icons);
    stbi_image_free(icons[0].pixels);
	

  /*  glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrollEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.m_Scrollevent(event);

        });*/


    glewExperimental = GL_TRUE;

    glewInit();

  
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
	
}

glWindow::~glWindow()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void glWindow::OnUpdate()
{
 
    glfwPollEvents();
}

unsigned int glWindow::GetWidth() const
{
    return m_Width;
}

unsigned int glWindow::GetHeight() const
{
    return m_Height;
}

void glWindow::PollEvent()
{
    glfwPollEvents();
}

void glWindow::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void glWindow::EnableVSync(bool enabled)
{
    VSync = enabled;

    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

bool glWindow::IsVSync()
{
    return VSync;
}

void glWindow::SetSize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

void glWindow::Clear()
{
    glViewport(0, 0, m_Width, m_Height);
    glClearColor(210.f / 255.f, 223.f / 255.f, 234.f / 255.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
}

void glWindow::Close()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void glWindow::SetFullscreen()
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    m_Width = mode->width;
    m_Height = mode->height;
}

void glWindow::SetTitle(std::string title)
{
    glfwSetWindowTitle(m_Window, title.c_str());
}


bool glWindow::Closed() const
{
    return glfwWindowShouldClose(m_Window);
}

void glWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_Data.m_Scrollevent = callback;
}



GLFWwindow* glWindow::GetNativeWindow() const
{
	return m_Window;
}
