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

#include "../../Vendor/imgui/ImGuizmo.h"
#include "../../Vendor/imgui/imgui_internal.h"

#include <gtx/quaternion.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Runtime/Math/Math.h"

#include "GuiComponents/ObjectProperties.h"
#include "GuiComponents/ContentBrowserPanel.h"

#include "../../Runtime/Utils/PlatformUtils.h"

#include "SceneSerializer.h"

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
	SceneHierarchy* m_SceneHierarchy;
	ObjectAdditor* m_ObjectAdditor;
	GuiConsole* m_Console;
	SceneProps* m_SceneProps; 
	ObjectProperties* m_ObjectProperties;
	ContentBrowserPanel* m_ContentBrowser;
	int m_SceneHierarchyCounter;
	bool _drawGrid = false;
	int m_GizmosType = -1;
	//std::unique_ptr<FrameBuffer> m_FrameBuffer;

	SceneSerializer* m_SceneSerializer;
	LightPoint* lightPoint;


};

#endif
