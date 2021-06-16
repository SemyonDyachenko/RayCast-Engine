#include "EditorObjectController.h"


EditorObjectController::EditorObjectController(glm::vec3 position)
{
	m_Mode = EditorObjectControllerMode::Translate;
	m_Xposition = glm::vec3(position.x-0.5f, position.y, position.z - 0.5f  + 1.0f);
	m_Yposition = glm::vec3(position.x, position.y, position.z  + 1.f);
	m_Zposition = glm::vec3(position.x, position.y+0.5f, position.z - 0.5f + 1.0f);
	InitMesh();
}

EditorObjectController::~EditorObjectController()
{
}

void EditorObjectController::SelectMode(EditorObjectControllerMode mode)
{
	m_Mode = mode;
}

void EditorObjectController::OnUpdate(float DeltaTime)
{
}

void EditorObjectController::OnRender(Shader* shader)
{
	shader->use();
	shader->SetMat4("ModelMatrix", xModelMatrix);
	xAxis->OnRender(*shader);
	shader->use();
	shader->SetMat4("ModelMatrix", yModelMatrix);
	yAxis->OnRender(*shader);
	shader->use();
	shader->SetMat4("ModelMatrix", zModelMatrix);
	zAxis->OnRender(*shader);
	shader->use();
}

void EditorObjectController::InitMesh()
{
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec2(0.f, 1.f),				glm::vec3(1.f, 0.f, 0.f), 				glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec2(0.f, 0.f),				glm::vec3(0.f, 1.f, 0.f),				glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.f),		glm::vec2(1.f, 0.f), 				glm::vec3(0.f, 0.f, 1.f),				glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, 0.5f, 0.f),			glm::vec2(1.f, 1.f), 				glm::vec3(1.f, 1.f, 0.f),				glm::vec3(0.f, 0.f, 1.f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2,	//Triangle 1
		0, 2, 3		//Triangle 2
	};
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	xModelMatrix = glm::mat4(1.0f);
	xModelMatrix = glm::translate(xModelMatrix, m_Xposition);
	xModelMatrix = glm::scale(xModelMatrix, glm::vec3(1.f, 0.015f,0.015f));

	yModelMatrix = glm::mat4(1.0f);
	yModelMatrix = glm::translate(yModelMatrix, m_Yposition);
	yModelMatrix = glm::rotate(yModelMatrix, glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));;
	yModelMatrix = glm::scale(yModelMatrix, glm::vec3(1.f, 0.15f, 0.055f));

	zModelMatrix = glm::mat4(1.0f);
	zModelMatrix = glm::translate(zModelMatrix, m_Zposition);
	zModelMatrix = glm::rotate(zModelMatrix, glm::radians(-90.f), glm::vec3(0.0f, 0.0f, 1.0f));;
	zModelMatrix = glm::scale(zModelMatrix, glm::vec3(1.f, 0.015f, 0.015f));

	xAxis = new Mesh(vertices,nrOfVertices,indices,nrOfIndices);
	yAxis = new Mesh(vertices,nrOfVertices,indices,nrOfIndices);
	zAxis = new Mesh(vertices,nrOfVertices,indices,nrOfIndices);
}

