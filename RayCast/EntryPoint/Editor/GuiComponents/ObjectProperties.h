#ifndef OBJECT_PROPERTIES 
#define OBJECT_PROPERTIES


#include "../EditorScene.h"
#include "GuiConsole.h"
#include "SceneHierarchy.h"

class ObjectProperties
{	
public:

	ObjectProperties();

	virtual ~ObjectProperties();

	void OnUpdate(float DeltaTime);

	void OnRender(EditorScene& scene,GuiConsole & console,SceneHierarchy& sceneHierarchy);

private:
	unsigned int m_ObjectId = -1;
	EditorSceneObject* m_Object;



	//material popup
	char texture_filename[256];

	glm::vec3 ambient = { 0.0f,0.0f,0.0f };
	glm::vec3 diffuse = { 0.0f,0.0f,0.0f };
	glm::vec3 specular = { 0.0f,0.0f,0.0f };

	Texture* diffuseTexture;
	Texture* specularTexture;
	Material* material;
	glm::vec3 material_color;
};


#endif