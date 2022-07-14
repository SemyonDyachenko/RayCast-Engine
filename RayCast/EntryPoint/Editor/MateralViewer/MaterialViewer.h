#ifndef MATERIAL_VIEWER_H
#define MATERIAL_VIEWER_H

#include "MaterialScene.h"

#include "../../../Vendor/imgui-docking/imgui.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../NodeEditor/NodeCreater.h"

#include "../Utils/IconsFontAwesome5.h"
#include "../Utils/TimeUtil.h"



class MaterialViewer
{
public:
	MaterialViewer();

	virtual ~MaterialViewer();

	void Update(float deltaTime);
	
	void ApplyMaterial();

	void Render(SceneHierarchy& sceneHierarchy,GuiConsole & console);

	void Open() { m_Opened = true; }
	void Close() { m_Opened = false; }

private:
	MaterialScene* m_Scene;

	MaterialStructure m_Structure;
	Texture* m_Transparent;

	bool m_Opened = false;

	std::string m_CurrentMaterialPath = "";
};

#endif