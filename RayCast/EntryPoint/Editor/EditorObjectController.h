#ifndef EDITOR_OBJECT_CONTROLLER
#define EDITOR_OBJECT_CONTROLLER

#include "../../Runtime/Rendering/Shader.h"
#include "../../Runtime/Rendering/Mesh.h"


class EditorObjectController
{
public:
	EditorObjectController();
	virtual ~EditorObjectController();

	//glm::vec3

	void OnUpdate(float DeltaTime);
	void OnRender(Shader* shader);
private:
	Mesh* xAxis;
	Mesh* yAxis;
	Mesh* zAxis;

	glm::vec3 m_Xposition;
	glm::vec3 m_Yposition;
	glm::vec3 m_Zposition;
};

#endif