#include "../../stdafx.h"
#include "EditorScene.h"
#include "../../Runtime/Core/Game.h"



void EditorScene::OnCreate()
{
	m_MainCamera = new Camera(glm::vec3(0.0f, 2.0f, 5.f), static_cast<float>(Game::GetWindow().GetWidth()) / static_cast<float>(Game::GetWindow().GetHeight()), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 60.f, 0.1f, 1000.f);
	m_editorShader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	m_EntitiesCount = m_Manager.GetEntitiesCount();
	m_PhysicsWorld = new DynamicWorld();
	physicsSimulation = false;

	m_Terrain = new Terrain(128.f, 128.f);
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


unsigned int EditorScene::GetEntitiesCount()
{
	return  m_EntitiesCount;
}

void EditorScene::RecalculateEntitiesCount()
{
	m_EntitiesCount = m_Manager.GetEntitiesCount();
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

}

void EditorScene::OnUpdate(float DeltaTime)
{

	m_MainCamera->OnUpdate(DeltaTime, Game::GetWindow().GetNativeWindow());



	m_editorShader->use();
	m_editorShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
	m_editorShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());

	m_editorShader->SetVec3("cameraPos", m_MainCamera->GetPosition());




	if (physicsSimulation) {
		if (m_PhysicsWorld->GetNumRigidBodies() != 0) {
			m_PhysicsWorld->Update(DeltaTime);
			for (auto& entity : m_Manager.GetEntities()) {
				if (entity->HasComponent<RigidBodyComponent>()) {
					auto& tc = entity->GetComponent<TransformComponent>();
					auto& rb = entity->GetComponent<RigidBodyComponent>();
					tc.Position = rb.rigidbody.GetPosition();
					tc.Rotation = glm::eulerAngles(rb.rigidbody.GetRotation());
				}

			}
		}
		else {
			ENGINE_WARNING("Number of rigid bodies = 0!!");
		}
	}
	else {
		for (auto& entity : m_Manager.GetEntities()) {
			if (entity->HasComponent<RigidBodyComponent>()) {
				auto& tc = entity->GetComponent<TransformComponent>();
				auto& rb = entity->GetComponent<RigidBodyComponent>();
				rb.rigidbody.Position = tc.Position;
			}
			
		}
	}

	for (auto& entity : m_Manager.GetEntities())
	{
		if (entity->HasComponent<AnimationComponent>()) {
			entity->GetComponent<AnimationComponent>().Update(DeltaTime);
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
	glm::mat4 modelmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) * glm::toMat4(glm::quat(glm::vec3(0.0f))) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

	m_editorShader->use();
	m_editorShader->SetMat4("ModelMatrix", modelmatrix);

	m_Terrain->OnRender(*m_editorShader);

	for (auto& entity : m_Manager.GetEntities()) {
		m_editorShader->use();

		if (entity->HasComponent<TransformComponent>()) {
			m_editorShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
		}

		if (entity->HasComponent<MaterialComponent>()) {
			auto& materialComponent = entity->GetComponent<MaterialComponent>();
			if (materialComponent.material.IsActive()) {
				m_editorShader->use();
				m_editorShader->setBool("textured", true);
				materialComponent.material.SetUniforms(*m_editorShader);
			}
			else {
				m_editorShader->setBool("textured", false);
			}
		}
		else {
			m_editorShader->setBool("textured", false);
		}

		if (entity->HasComponent<MeshComponent>()) {
			entity->GetComponent<MeshComponent>().mesh.OnRender(*m_editorShader);
		}

		if (entity->HasComponent<DirectionalLightComponent>()) {
			entity->GetComponent<DirectionalLightComponent>().light.SetUniforms(*m_editorShader);
		}

		if (entity->HasComponent<LightPointComponent>()) {
			entity->GetComponent<LightPointComponent>().light.SetUniforms(*m_editorShader);
		}

		/*if (entity->HasComponent<AnimationComponent>()) {
			entity->GetComponent<AnimationComponent>().model.Draw(*m_editorShader);
		}*/


	}

}