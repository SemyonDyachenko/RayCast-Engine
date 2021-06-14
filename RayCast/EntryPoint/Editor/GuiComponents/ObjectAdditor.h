#ifndef OBJECT_ADDITOR_H
#define OBJECT_ADDITOR_H

#include "../EditorScene.h"
#include "SceneHierarchy.h"
#include "GuiConsole.h"

enum class DefaultObjects {
	Plane = 0,
	Sphere = 1,
	Cylinder = 2,
	Cube = 3,
	Monkey = 4
};

class ObjectAdditor
{
public:
	ObjectAdditor();

	virtual ~ObjectAdditor() = default;

	void Update(float DeltaTime);

	void Render(EditorScene & editorScene,SceneHierarchy* sceneHierarchy,GuiConsole* console);

	EditorSceneObject* CreateDefaultObject(DefaultObjects index, std::string name, unsigned int id);

	std::string CalculateTime();

private:

};

#endif