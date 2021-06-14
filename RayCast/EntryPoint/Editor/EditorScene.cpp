#include "EditorScene.h"
#include "../../Runtime/Core/Game.h"

void EditorScene::OnCreate()
{
	m_MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 2.f), static_cast<float>(Game::GetWindow().GetWidth()) / static_cast<float>(Game::GetWindow().GetHeight()), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 90.f, 0.1f, 1000.f);
	m_editorShader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	m_ObjectCount = 0;
}

void EditorScene::OnDestroy()
{
}

void EditorScene::ImGuiScene()
{


	ImGui::Begin("Scene");


	ImGui::End();
}

void EditorScene::OnActivate()
{
}

void EditorScene::OnDeactivate()
{
}

void EditorScene::AddObject(EditorSceneObject* object)
{
	m_Objects.push_back(object);
	m_ObjectCount++;
}

void EditorScene::DeleteObject(std::string name)
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->GetName() == name) {
				delete m_Objects[i];
				break;
				m_ObjectCount--;
			}
		}
	}
}

unsigned int EditorScene::GetObjectCount() const
{
	return m_ObjectCount;
}

void EditorScene::OnUpdate(float DeltaTime)
{
	

	m_MainCamera->OnUpdate(DeltaTime, Game::GetWindow().GetNativeWindow());


	m_editorShader->use();
	m_editorShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
	m_editorShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());
	m_editorShader->SetVec3("lightPos0", m_MainCamera->GetPosition());
	m_editorShader->SetVec3("cameraPos", m_MainCamera->GetPosition());


	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			m_Objects[i]->Update(DeltaTime);

		}
	}
}

void EditorScene::OnRender()
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			m_editorShader->use();
			m_editorShader->SetMat4("ModelMatrix", m_Objects[i]->GetModelMatrix());
			m_Objects[i]->Render(m_editorShader);
		}
	}
}

std::vector<EditorSceneObject*> EditorScene::GetObjects()
{
	return m_Objects;
}
