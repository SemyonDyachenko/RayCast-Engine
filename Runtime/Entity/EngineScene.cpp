
#include "EngineScene.h"

/*
Entity EngineScene::CreateEntity(unsigned int id, const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	entity.SetName(name);
	entity.SetId(id);
	return entity;
}

void EngineScene::DestroyEntity(Entity entity)
{
	m_Registry.destroy(entity);
}

void EngineScene::OnUpdate(float DeltaTime)
{
	if (m_Shader) {
		m_Shader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());
		m_Shader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
	}
}

void EngineScene::OnRender()
{
	auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);

	for (auto entity : group) {
		auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		
		if (m_Shader) {
			m_Shader->SetMat4("ModelMatrix", transform.GetTrasnform());

			mesh.mesh.OnRender(*m_Shader);
		}
	}
}



template<typename T>
void EngineScene::OnComponentAdded(Entity entity, T& component)
{
	static_assert(false);
}


template<>
void EngineScene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
{
}

template<>
void EngineScene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
{

}

template<>
void EngineScene::OnComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
{
}

template<>
void EngineScene::OnComponentAdded<AnimationComponent>(Entity entity, AnimationComponent& component)
{
}

template<>
void EngineScene::OnComponentAdded<ColorComponent>(Entity entity, ColorComponent& component)
{
}
*/