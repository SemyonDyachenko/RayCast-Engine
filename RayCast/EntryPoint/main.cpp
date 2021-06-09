#include "../Runtime/Core/Game.h"
#include "../Runtime/Core/Core.h"

#define _WIN32
#define GAME_MODE

WindowProps * props = new WindowProps();

extern Game* CreateGame();

int main(int argc, char** argv)
{

    auto game = CreateGame();

    game->Run();
    
    game->Shutdown();
    delete game;
    
    
    return 0;
}