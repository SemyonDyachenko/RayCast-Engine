#include "EditorScene.h"
#include "../../Runtime/Core/Game.h"



void EditorScene::OnCreate()
{
	m_MainCamera = new Camera(glm::vec3(0.0f, 2.0f, 5.f), static_cast<float>(Game::GetWindow().GetWidth()) / static_cast<float>(Game::GetWindow().GetHeight()), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 60.f, 0.1f, 1000.f);
	m_editorShader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	m_EntitiesCount = m_Manager.GetEntitiesCount();
}

void EditorScene::OnDestroy()
{
}

void EditorScene::ImGuiScene()
{
}

void EditorScene::OnActivate()
{
}

void EditorScene::OnDeactivate()
{
}

Entity& EditorScene::CreateEntity(unsigned int id, std::string name)
{
	return m_Manager.CreateEntity(id, name);
}

void EditorScene::DeleteEntity(unsigned int id)
{
	m_Manager.DeleteEntity(id);
	//RecalculateEntitiesCount();
}


std::unique_ptr<Entity>& EditorScene::GetEntity(unsigned int id)
{
	for (auto& entity : m_Manager.GetEntities()) {
		if (entity->GetId() == id) {
			return entity;
	
		}
	
		
	}
}

void EditorScene::AddLightPoint(LightPoint* lightPoint)
{
	m_LightPoint = lightPoint;
}

void EditorScene::AddObject(EditorSceneObject* object)
{
	m_Objects.push_back(object);
	m_ObjectCount++;
}

void EditorScene::DeleteObject(unsigned int id)
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->GetId() == id) {
				m_Objects.erase(m_Objects.begin()+i);
			}
		}
	}
}

unsigned int EditorScene::GetObjectCount() const
{
	return m_ObjectCount;
}

unsigned int EditorScene::GetEntitiesCount()
{
	return  m_EntitiesCount;
}

void EditorScene::RecalculateEntitiesCount()
{
	m_EntitiesCount = m_Manager.GetEntitiesCount();
}

EditorSceneObject* EditorScene::GetSelectedObject()
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->Selected()) {
				return m_Objects[i];
			}
			else {
				return nullptr;
			}
		}
	}
}

void EditorScene::SelectObject(unsigned int id)
{

	for (size_t i = 0; i < m_Objects.size(); i++) {
		if (m_Objects[i]->GetId() == id) {
			m_Objects[i]->Select(true);
		} 
	}
}

void EditorScene::UnselectObject(unsigned int id)
{
	assert(m_Objects.size() != 0);
	for (size_t i = 0; i < m_Objects.size(); i++) {
			m_Objects[i]->Select(false);
	}
}

EditorSceneObject* EditorScene::GetObjectById(unsigned int id)
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			if (m_Objects[i]->GetId() == id) {
				return m_Objects[i];
			}
		}
	}
	else {
		return nullptr;
	}
}



void EditorScene::UpdateMainCamera(float DeltaTime)
{
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::FORWARD, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::BACK, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::LEFT, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::RIGHT, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::UP, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		m_MainCamera->Move(EditorCameraDirection::DOWN, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		m_MainCamera->Rotate(EditorCameraRotationDirection::LEFT, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		m_MainCamera->Rotate(EditorCameraRotationDirection::RIGHT, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		m_MainCamera->Rotate(EditorCameraRotationDirection::UP, DeltaTime);
	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		m_MainCamera->Rotate(EditorCameraRotationDirection::DOWN, DeltaTime);
	}
		


}

void EditorScene::OnUpdate(float DeltaTime)
{

	m_MainCamera->OnUpdate(DeltaTime, Game::GetWindow().GetNativeWindow());



	m_editorShader->use();
	m_editorShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
	m_editorShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());
	if (!m_LightPoint)
		m_editorShader->SetVec3("lightPos0", m_MainCamera->GetPosition());
	else
		m_editorShader->SetVec3("lightPos0", m_LightPoint->GetPosition());

;	m_editorShader->SetVec3("cameraPos", m_MainCamera->GetPosition());


	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			m_Objects[i]->Update(DeltaTime);

		}
	}

	m_Manager.Update(DeltaTime);
}

Camera& EditorScene::GetMainCamera()
{
	return *m_MainCamera;
}

void EditorScene::OnRender()
{
	if (m_Objects.size() != 0) {
		for (size_t i = 0; i < m_Objects.size(); i++) {
			m_editorShader->use();
			m_editorShader->SetMat4("ModelMatrix", m_Objects[i]->GetModelMatrix());

			if(m_LightPoint)
				m_LightPoint->SetUniforms(*m_editorShader);

			m_Objects[i]->Render(m_editorShader);
		}
	}
	
		for (auto& entity : m_Manager.GetEntities()) {
			m_editorShader->use();

			if (entity->HasComponent<TransformComponent>()) {
				m_editorShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
			}

			if (entity->HasComponent<MaterialComponent>()) {
				m_editorShader->setBool("textured",true);
				entity->GetComponent<MaterialComponent>().material.SetUniforms(*m_editorShader);
			}

			if (entity->HasComponent<MeshComponent>()) {
				entity->GetComponent<MeshComponent>().mesh.OnRender(*m_editorShader);
			}
		}

}

std::vector<EditorSceneObject*> EditorScene::GetObjects()
{
	return m_Objects;
}
