
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


Game* Game::s_Instance = nullptr;

static WindowProps props{"Default App",1440,900,false,false};
std::unique_ptr<Window> Game::m_Window = Window::Create(props);


Game::Game(const std::string& name)
{
    Init(props);
    s_Instance = this;

}

void Game::Init(WindowProps& props)
{
    isRunning = true;
    m_IsPlayMode = true;
}

void Game::PushLayer(Layer* layer)
{
    m_Layers.PushLayer(layer);
    layer->Attach();
}


void Game::Shutdown()
{
    isRunning = false;
    m_Window->Close();
}

void Game::Run()
{
    while (!m_Window->Closed()) {

        float time = (float)glfwGetTime();
        float deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;


        m_Window->Clear();
        m_Window->PollEvent();

        for (Layer* layer : m_Layers) {
            layer->Update(deltaTime);
            layer->Render();
        }

        m_Window->SwapBuffers();
       
    }
}
