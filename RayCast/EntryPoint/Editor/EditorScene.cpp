#include "EditorScene.h"

void EditorScene::OnCreate()
{

	m_MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.f), static_cast<float>(1280) / static_cast<float>(720), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 90.f, 0.1f, 1000.f);

	FrameBufferProps props;
	props.Width = 1280;
	props.Height = 720;
	m_FrameBuffer = FrameBuffer::Create(props);

	m_editorShader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	framebuffer_shader = new Shader("resources/shaders/framebuffer_vertex_shader.glsl", "resources/shaders/framebuffer_fragment_shader.glsl");
}

void EditorScene::OnDestroy()
{
}

void EditorScene::ImGuiScene()
{
	unsigned int textureID = m_FrameBuffer->GetTextureID();


	framebuffer_shader->use();
	framebuffer_shader->setInt("screenTexture", textureID);

	ImGui::Begin("Scene");

	ImGui::Image((void*)textureID, ImVec2{ 1280,720 });

	ImGui::End();
}

void EditorScene::OnActivate()
{
}

void EditorScene::OnDeactivate()
{
}

void EditorScene::OnUpdate(float DeltaTime)
{
	m_editorShader->use();
	m_editorShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
	m_editorShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());
	m_editorShader->SetVec3("lightPos0", m_MainCamera->GetPosition());
	m_editorShader->SetVec3("cameraPos", m_MainCamera->GetPosition());
	m_editorShader->unuse();

	for (size_t i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->Update(DeltaTime);
	}
}

void EditorScene::OnRender()
{
	for (size_t i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->Render(m_editorShader);
	}
}
