#include "glWindow.h"



glWindow::glWindow(RayCast::WindowProps& props)
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

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_Window);

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            RayCast::MouseScrollEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.m_Scrollevent(event);

        });


    glewExperimental = GL_TRUE;

    glewInit();

   
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_MULTISAMPLE);

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
