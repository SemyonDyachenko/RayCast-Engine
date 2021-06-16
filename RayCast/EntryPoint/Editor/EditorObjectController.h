#ifndef EDITOR_OBJECT_CONTROLLER
#define EDITOR_OBJECT_CONTROLLER

#include "../../Runtime/Rendering/Shader.h"
#include "../../Runtime/Rendering/Mesh.h"

enum class EditorObjectControllerMode {
	Translate = 0,
	Rotate,
	Scale
};


class EditorObjectController
{
public:
	EditorObjectController(glm::vec3 position);
	virtual ~EditorObjectController();

	//glm::vec3
	void SelectMode(EditorObjectControllerMode mode);

	void OnUpdate(float DeltaTime);
	void OnRender(Shader* shader);
private:
	void InitMesh();

	Mesh* xAxis;
	Mesh* yAxis;
	Mesh* zAxis;

	glm::vec3 m_Xposition;
	glm::vec3 m_Yposition;
	glm::vec3 m_Zposition;

	glm::mat4 xModelMatrix;
	glm::mat4 yModelMatrix;
	glm::mat4 zModelMatrix;

	EditorObjectControllerMode m_Mode;
};

#endif