#pragma once
/*
#include <entt/entt.hpp>

#include "Entity.h"
#include "../Core/Game.h"

class Entity;

class EngineScene
{
public:
	EngineScene() {
		m_MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 2.f), static_cast<float>(Game::GetWindow().GetWidth()) / static_cast<float>(Game::GetWindow().GetHeight()), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 90.f, 0.1f, 1000.f);
	}

	~EngineScene() {

	}

	Entity CreateEntity(unsigned int id,const std::string& name = std::string());
	void DestroyEntity(Entity entity);

	void OnUpdate(float DeltaTime);

	void OnRender();

	void SetMainShader(Shader* shader) { m_Shader = shader; }

private:
	template<typename T>
	void OnComponentAdded(Entity entity, T& component);

private:
	entt::registry m_Registry;

	Shader* m_Shader;
	Camera* m_MainCamera;

	friend class Entity;
};
*/