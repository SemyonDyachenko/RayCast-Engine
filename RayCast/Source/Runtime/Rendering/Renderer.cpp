#include "Renderer.h"

void Renderer::Init()
{
}

void Renderer::SubmitCamera(Shader*shader,Camera* camera)
{
	shader->use();
	shader->SetMat4("ViewMatrix", camera->GetViewMatrix());
	shader->SetMat4("ProjectionMatrix",camera->GetProjectionMatrix());
}

void Renderer::Render(Shader* shader, Mesh* mesh, glm::mat4 transformation)
{
	shader->use();
	shader->SetMat4("ModelMatrix", transformation);

	mesh->OnRender(*shader);
}
