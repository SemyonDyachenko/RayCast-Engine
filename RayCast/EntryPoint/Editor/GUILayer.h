#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include <GL/glew.h>
#include "EditorScene.h"
#include <iostream>
#include "../../Runtime/Core/Layer.h"
#include "../../Runtime/Core/Game.h"
#include "../Game/Scenes/StateMachine.h"
#include <GLFW/glfw3.h>


enum class MenuBar {
	Save = 0,
	View = 1,

};

class GUILayer : public Layer
{
public:
	GUILayer();
	~GUILayer();

	void Attach() override;
	void Detach() override;
	void OnEvent() override;
	void Update(float DeltaTime) override;
	void Render() override;
private:
	GLFWwindow* m_Window;
	StateMachine* m_stateMachie;
	std::shared_ptr<EditorScene> m_EditorScene;
	std::unique_ptr<FrameBuffer> m_FrameBuffer;
};

#endif
