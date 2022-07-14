#ifndef APP_GAME_H
#define APP_GAME_H

#include "../Runtime/Core/Game.h"
#include "GameLayer.h"
#include "EditorLayer.h"

class AppGame : public Game
{
public:

	AppGame();

	virtual ~AppGame() = default;

};


#endif