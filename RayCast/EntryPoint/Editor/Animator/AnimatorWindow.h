#ifndef ANIMATOR_WINDOW_H
#define ANIMATOR_WINDOW_H

#include "../SceneHierarchy/SceneHierarchy.h"
#include "../../../Vendor/imgui-docking/ImGuizmo.h"
#include "AnimationScene.h"

class AnimatorWindow
{
public:
	AnimatorWindow();

	virtual ~AnimatorWindow();

	void Update(float DeltaTime);

	void Render(SceneHierarchy& sceneHierarchy);
	
	void Open() { m_Opened = true; }
	void Close() { m_Opened = false; }

private:
	bool m_Opened = false;
	AnimationScene* m_Scene;
};

#endif