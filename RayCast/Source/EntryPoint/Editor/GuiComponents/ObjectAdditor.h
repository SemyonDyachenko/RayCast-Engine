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

	bool& OnPopupEvent();

	Mesh* AddMesh(DefaultObjects object);

	void AddEntity(DefaultObjects object,std::string name,EditorScene& target,GuiConsole & console);
	void AddEntity(std::string meshPath,std::string name,EditorScene& target,GuiConsole & console);

	void Render(EditorScene & editorScene,SceneHierarchy* sceneHierarchy,GuiConsole* console);

	Mesh* CreateDefaultEntity(DefaultObjects index, std::string name, unsigned int id);

	std::string CalculateTime();

private:
	char m_NewObjectNameBuffer[60] = "";
	char m_NewObjectTypeBuffer[60] = "";
	char m_NewObjectModelPath[128] = "";
	glm::vec3 m_NewObjectPosition = { 0.0f,0.0f,0.0f };

	bool m_OnPopup = false;

	unsigned int m_ObjectsCount;

};

#endif