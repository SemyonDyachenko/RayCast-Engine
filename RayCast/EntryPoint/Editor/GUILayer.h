#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include <iostream>
#include "../../Runtime/Core/Layer.h"
#include "../../Runtime/Core/Game.h"
#include "../../Vendor/imgui/imgui.h"
#include "../../Vendor/imgui/imgui_impl_glfw.h"
#include "../../Vendor/imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "../Game/Scenes/StateMachine.h"


class EditorScene : public Scene {
public:

};

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
};

#endif
