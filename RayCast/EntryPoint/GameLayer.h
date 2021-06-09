#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "../Runtime/Core/Layer.h"
#include "Game/Scenes/StateMachine.h"


class GameLayer : public Layer
{
public:
	GameLayer();

	~GameLayer();

	void OnEvent() override;

	void Update(float deltaTime) override;

	void Render() override;

private:
	StateMachine* m_sceneStateMachine;
};

#endif