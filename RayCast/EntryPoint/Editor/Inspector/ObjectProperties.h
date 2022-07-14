#ifndef OBJECT_PROPERTIES 
#define OBJECT_PROPERTIES


#include "../EditorScene.h"
#include "../GuiComponents/GuiConsole.h"
#include "../SceneHierarchy//SceneHierarchy.h"

#include <filesystem>
#include "../Utils/TimeUtil.h"

#include "../../../Runtime/Core/Input.h"
#include "../../../Runtime/Utils/PlatformUtils.h"



#include "../../../Runtime/Utils/FilesystemUtils.h"

class ObjectProperties
{
public:

	ObjectProperties(SceneHierarchy& sceneHierarchy);

	virtual ~ObjectProperties();

	std::string GetTexturePath();

	void OnUpdate(float DeltaTime);

	void OnRender(EditorScene& scene, GuiConsole& console);

private:
	SceneHierarchy* m_SceneHierarchy;

	unsigned int m_ObjectId = -1;
	Texture* m_Transparent;

	glm::vec3 ambient = { 0.0f,0.0f,0.0f };
	glm::vec3 diffuse = { 0.0f,0.0f,0.0f };
	glm::vec3 specular = { 0.0f,0.0f,0.0f };
};


#endif