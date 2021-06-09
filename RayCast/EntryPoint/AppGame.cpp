#include "AppGame.h"

AppGame::AppGame()
{
	this->PushLayer(new EditorLayer());
}

Game* CreateGame() {
	return new AppGame();
}
