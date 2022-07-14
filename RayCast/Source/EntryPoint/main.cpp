#include "../stdafx.h"
#include "../Runtime/Core/Game.h"
#include "../Runtime/Core/Core.h"
#include "../Runtime/Core/Log.h"

#define _WIN32
#define DEBUG_MODE

WindowProps * props = new WindowProps();

extern Game* CreateGame();

int main(int argc, char** argv)
{
    Log::Init();
    ENGINE_WARNING("Initialized Logger!");

    auto game = CreateGame();

    game->Run();
    
    game->Shutdown();
    delete game;
    
    
    return 0;
}