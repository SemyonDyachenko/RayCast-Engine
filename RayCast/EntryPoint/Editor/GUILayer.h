#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include <GL/glew.h>
#include "EditorScene.h"
#include <iostream>
#include "../../Runtime/Core/Layer.h"
#include "../../Runtime/Core/Game.h"
#include "../../Runtime/Entity/StateMachine.h"
#include <GLFW/glfw3.h>
#include "SceneHierarchy/SceneHierarchy.h"
#include "GuiComponents/GuiConsole.h"
#include "GuiComponents/EntityCreator.h"
#include <chrono>
#include "GuiComponents/SceneProps.h"

//#include "../../Vendor/imgui/ImGuizmo.h"
//#include "../../Vendor/imgui/imgui_internal.h"
#include "../../Vendor/imgui-docking/imgui.h"
#include "../../Vendor/imgui-docking/imgui_internal.h"

#include "Utils/MousePicker.h"



#include <gtx/quaternion.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Runtime/Math/Math.h"

#include "Inspector/ObjectProperties.h"
#include "ContentBrowser/ContentBrowserPanel.h"

#include "../../Runtime/Utils/PlatformUtils.h"

#include "../../Runtime/Serializing/SceneSerializer.h"

#include "Utils/IconsFontAwesome5.h"

#include "MateralViewer/MaterialViewer.h"

#include "Animator/AnimatorWindow.h"

#include "TerrainEditor/TerrainEditor.h"

#pragma warning(disable : 4996) 
#include <iomanip>



#define NATIVE_WINDOW GLFWwindow


class GUILayer : public Layer
{
public:
	GUILayer();
	~GUILayer() = default;

	void Attach() override;
	void Detach() override;
	void OnEvent() override;
	void Update(float DeltaTime) override;
	void Render() override;

	void HandleShortcuts();

	// local
	void SetImGuiTheme();


private:
	NATIVE_WINDOW* m_Window;
	StateMachine* m_stateMachine;
	std::shared_ptr<EditorScene> m_EditorScene;
	SceneHierarchy* m_SceneHierarchy;
	ObjectAdditor* m_ObjectCreator;
	GuiConsole* m_Console;
	SceneProps* m_SceneProps;
	ObjectProperties* m_ObjectProperties;
	ContentBrowserPanel* m_ContentBrowser;
	MaterialViewer* m_MaterialViewer;
	AnimatorWindow* m_Animator;
	TerrainEditor* m_TerrainEditor;
	EntityCreator* m_EntityCreator;

	MousePicker* m_MouseRay;



	bool _drawGrid = false;
	int m_GizmosType = -1;
	glm::vec2 m_InitialMousePos;

	SceneSerializer* m_SceneSerializer;
	std::string m_SceneFilename;

	glm::vec2 m_ViewportBounds[2];
	float m_ViewPortWidth = 0, m_ViewPortHeight = 0;
	bool m_ViewportFocused;

};

#endif
