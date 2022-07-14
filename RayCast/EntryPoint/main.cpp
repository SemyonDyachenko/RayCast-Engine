#include "../stdafx.h"
#include "../Runtime/Core/Game.h"
#include "../Runtime/Core/Core.h"
#include "../Runtime/Core/Log.h"

#ifdef PRODUCTION_BUILD
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define DEBUG_MODE
#define IMGUI_LAYER

WindowProps * props = new WindowProps();

extern Game* CreateGame();

const GLubyte* vendor = glGetString(GL_VENDOR);
const GLubyte* renderer = glGetString(GL_RENDERER);
const GLubyte* extensions = glGetString(GL_EXTENSIONS);
const GLubyte* shadingVer = glGetString(GL_SHADING_LANGUAGE_VERSION);


int main(int argc, char** argv)
{

#ifdef DEBUG_MODE
    std::cout << "RayCast Engine 1.0" << std::endl;
    std::cout << "Vendor: " << vendor << std::endl;
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "Shading version (GLSL): " << shadingVer << std::endl;
#endif

    Log::Init();
    ENGINE_WARNING("Initialized Logger!");

    auto game = CreateGame();

    game->Run();
    
    game->Shutdown();
    delete game;
    
    
    return 0;
}