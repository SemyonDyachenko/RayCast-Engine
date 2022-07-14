#include <iostream>

#include <Runtime/Core/Engine.h>


extern RayCast::Game* CreateGame();


int main(int argc, char** argv)
{
    RayCast::Log::Init();

    auto game = CreateGame();

    game->Run();

    game->Shutdown();
    delete game;


    return 0;
}