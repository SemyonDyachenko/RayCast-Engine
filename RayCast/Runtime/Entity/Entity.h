#pragma once

#include <GL/glew.h>
#include <string>
#include "Component.h"
#include <vector>

#include <array>
#include <bitset>


class Component;


enum class EntityType {
	STATIC,
	DYNAMIC
};

class Entity
{
public:

	std::string GetName() { return m_Name;  }
	unsigned int GetId() { return m_Id;  }

	template<typename T>
	bool HasComponent() const {
		return m_ComponentsBitset[GetComponentTypeID<T>()];
	}

	template<typename T,typename... TArgs>	
	T& AddComponent(TArgs&&... mArgs) {
		T* component(new T(std::forward <TArgs>(mArgs)...));
		component->entity = this;
		std::shared_ptr<Component> uPtr{ component };
		m_Components.emplace_back(std::move(uPtr));
			
		m_ComponentsArray[GetComponentTypeID<T>()] = component;
		m_ComponentsBitset[GetComponentTypeID<T>()] = true;


		return *component;	
	}

	template<typename T>
	void RemoveComponent() {
	}


	template<typename T>
	T& GetComponent() const {
	auto pointer(m_ComponentsArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(pointer); 
	}

	void SetName(std::string name) { m_Name = name; }
	void SetId(unsigned int id) { m_Id = id; }

	virtual void OnUpdate(float DeltaTime) {
	
	}

	bool Selected() const {
		return m_Selected;
	}

private:
	std::string m_Name;
	unsigned int m_Id;
	std::vector<std::shared_ptr<Component>> m_Components;
	bool m_Selected;

	std::bitset<MAX_COMPONENTS> m_ComponentsBitset;
	std::array<Component*, MAX_COMPONENTS> m_ComponentsArray;

};

