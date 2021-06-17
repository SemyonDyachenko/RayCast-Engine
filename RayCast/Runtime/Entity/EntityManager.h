#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <GL/glew.h>
#define MAX_ENTITIES 10000

#include "Entity.h"


class EntityManager {
public:
	void Update(float DeltaTime) {
		if (!m_Entities.empty()) {
			for (auto& entity : m_Entities)
				entity->OnUpdate(DeltaTime);
		}
	}

	
	Entity& CreateEntity(unsigned int id,std::string name) {
		Entity* e = new Entity();
		e->SetId(id);
		e->SetName(name);
		e->AddComponent<TransformComponent>();   
		std::unique_ptr<Entity> uPtr{ e };
		m_Entities.emplace_back(std::move(uPtr));

		return *e;
	}

	void DeleteEntity(unsigned int id) {
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i]->GetId() == id) {
				std::cout << i << "\n";
				m_Entities.erase(m_Entities.begin() + i);
			}
		}
	}

	void Clear() {
		m_Entities.clear();
	}

	unsigned int GetEntitiesCount() {
		return m_Entities.size();
	}

	std::vector<std::unique_ptr<Entity>>& GetEntities() {
		return m_Entities;
	}

private:
	std::vector<std::unique_ptr<Entity>> m_Entities;

};

#endif