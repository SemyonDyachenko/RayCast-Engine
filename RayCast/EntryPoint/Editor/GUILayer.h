#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include <GL/glew.h>
#include "EditorScene.h"
#include <iostream>
#include "../../Runtime/Core/Layer.h"
#include "../../Runtime/Core/Game.h"
#include "../Game/Scenes/StateMachine.h"
#include <GLFW/glfw3.h>
#include "GuiComponents/SceneHierarchy.h"
#include "GuiComponents/GuiConsole.h"
#include <chrono>
#include "GuiComponents/SceneProps.h"

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

	// local

	void CreateDefaultObject(DefaultObjects index, std::string name, unsigned int id);

private:
	GLFWwindow* m_Window;
	StateMachine* m_stateMachie;
	std::shared_ptr<EditorScene> m_EditorScene;
	SceneHierarchy* m_SceneHierarchy;
	ObjectAdditor* m_ObjectAdditor;
	GuiConsole* m_Console;
	SceneProps* m_SceneProps; 
	int m_SceneHierarchyCounter;
	//std::unique_ptr<FrameBuffer> m_FrameBuffer;

};

#endif
