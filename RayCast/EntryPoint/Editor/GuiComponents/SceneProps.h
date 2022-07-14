#ifndef SCENE_PROPS_H
#define SCENE_PROPS_H

#include "ObjectAdditor.h"

#include "../../../Vendor/imgui-docking/ImGuizmo.h"

enum class TransformMode {
	Translate = 0,
	Rotate = 1,
	Scale = 2
};

class SceneProps
{
public:
	SceneProps();

	virtual ~SceneProps() = default;

	int GetGizmosType() const;

	void SetGizmosType(int type);
	
	TransformMode GetTransformMode() const;

	void Update(float DeltaTime);

	void Render(EditorScene& scene);
private:
	TransformMode m_TransformMode;
	int m_GizmosType = -1;

};

#endif