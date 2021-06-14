#ifndef SCENE_PROPS_H
#define SCENE_PROPS_H

#include "ObjectAdditor.h"

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
	
	TransformMode GetTransformMode();

	void Update(float DeltaTime);

	void Render();
private:
	TransformMode m_TransformMode;

};

#endif