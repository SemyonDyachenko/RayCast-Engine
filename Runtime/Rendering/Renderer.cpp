#include "Renderer.h"

namespace RayCast {

	void Renderer::Init()
	{

	}

	void Renderer::SetViewport(glm::vec4 viewport)
	{
	}

	void Renderer::SetClearColor(glm::vec3 color)
	{
	}

	void Renderer::SubmitCamera(Shader* shader, Camera* camera)
	{
		shader->use();
		shader->SetMat4("ViewMatrix", camera->GetViewMatrix());
		shader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());
	}

	void Renderer::Render(Shader* shader, Mesh* mesh, glm::mat4 transformation)
	{
		shader->use();
		shader->SetMat4("ModelMatrix", transformation);

		mesh->OnRender(*shader);
	}


}