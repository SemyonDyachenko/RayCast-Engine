#ifndef OBJECT_PROPERTIES 
#define OBJECT_PROPERTIES


#include "../EditorScene.h"
#include "GuiConsole.h"
#include "SceneHierarchy.h"

class ObjectProperties
{	
public:

	ObjectProperties(SceneHierarchy& sceneHierarchy);

	virtual ~ObjectProperties();

	void OnUpdate(float DeltaTime);

	void OnRender(EditorScene& scene);

private:
	SceneHierarchy* m_SceneHierarchy;

	unsigned int m_ObjectId = -1;
	EditorSceneObject* m_Object;

	glm::vec3 ambient = { 0.0f,0.0f,0.0f };
	glm::vec3 diffuse = { 0.0f,0.0f,0.0f };
	glm::vec3 specular = { 0.0f,0.0f,0.0f };
};


#endif