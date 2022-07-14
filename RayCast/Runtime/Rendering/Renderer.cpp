#include "Renderer.h"

std::shared_ptr<RendererAPI> Renderer::m_Renderer = RendererAPI::Create();

void Renderer::Init()
{
	m_Renderer->Init();
}

void Renderer::SetViewport(glm::vec4 viewport)
{
	m_Renderer->SetViewport(viewport.x, viewport.y, viewport.z, viewport.w);
}

void Renderer::SetClearColor(glm::vec3 color)
{
	m_Renderer->SetClearColor(color);
}

void Renderer::Clear()
{
	m_Renderer->Clear();
}

void Renderer::SubmitCamera(Shader*shader, EditorCamera* camera)
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

void Renderer::RenderTexturedQuad(EditorCamera* camera)
{
	
}


