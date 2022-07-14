#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <GL/glew.h>
// #define MAX_ENTITIES 64

#include "Entity.h"
#include "CameraComponent.h"

class EntityManager {
public:
	void Update(float DeltaTime) {
		if (!m_Entities.empty()) {
			for (auto& entity : m_Entities) {
				entity->OnUpdate(DeltaTime);

				/*	if (entity->HasComponent<NativeScriptComponent>()) {
						auto& nsc = entity->GetComponent<NativeScriptComponent>();
						if (!nsc.Instance) {
							nsc.Instance = nsc.InstantiateScript();
							nsc.Instance->m_Entity = *entity;
							nsc.Instance->OnCreate();
						}
						nsc.Instance->OnUpdate(DeltaTime);

					}*/
			}
		}
	}


	/* Return entity in array, if entity has Camera Component with primary flag. (Only one Entiy can have Camera Component with Primary flag!!) */
	Entity* GetPrimaryCamera()
	{
		for (auto& entity : m_Entities) {
			if(entity->HasComponent<CameraComponent>())
			{
				if(entity->GetComponent<CameraComponent>().Primary)
				{
					return &(*entity);
					break;
				}
			}
		}
		return nullptr;
	}

	// Return entity in array, by his ID (Reference to Entity)
	Entity& GetEntityById(unsigned int id) {
		for (size_t i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i]->GetId() == id) {
				return *m_Entities[i];
			}
		}
	}

	/* Creating default entity with Tag,Transform and Script Component */
	Entity& CreateEntity(unsigned int id, std::string name) {
		Entity* e = new Entity();
		e->SetId(id);
		e->SetName(name);
		e->AddComponent<TransformComponent>();
		e->AddComponent<TagComponent>(name);
		e->AddComponent<ScriptComponent>();
		std::unique_ptr<Entity> uPtr{ e };
		m_Entities.emplace_back(std::move(uPtr));

		return *e;
	}

	// Delete entity by Id
	void DeleteEntity(unsigned int id) {
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i]->GetId() == id) {
				m_Entities.erase(m_Entities.begin() + i);
			}
		}
	}


	// clear entity array
	void Clear() {
		m_Entities.clear();
	}


	//return size of entities array
	unsigned int GetEntitiesCount() const
	{
		return static_cast<unsigned>(m_Entities.size());
	}

	// return array of entity unique pointers
	std::vector<std::unique_ptr<Entity>>& GetEntities() {
		return m_Entities;
	}

private:
	std::vector<std::unique_ptr<Entity>> m_Entities;

};

#endif