#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "../Runtime/Core/Layer.h"
#include "Game/Scenes/StateMachine.h"
#include "../Animation/AnimatedModel.h"
#include "../Animation/Animator.h"
#include "../Runtime/Rendering/Shader.h"
#include "../Runtime/Rendering/Texture.h"
#include "../Runtime/Camera/Camera.h"



class GameLayer : public Layer
{
public:
	GameLayer();

	~GameLayer();

	void OnEvent() override;

	void Attach() override;

	void Detach() override;

	void Update(float deltaTime) override;

	void Render() override;

private:
	StateMachine* m_sceneStateMachine;

};

#endif