#pragma once

#ifndef SCEME_H
#define SCENE_H

#include "Entity.h"
#include "EntityManager.h"
#include "../Scripts/ScriptManager.h"

class Scene {
public:
	virtual ~Scene() = default;
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnActivate() = 0;

	virtual Entity& CreateEntity(unsigned int id, std::string name) = 0;
	virtual void DeleteEntity(unsigned int id) = 0;

	virtual void OnDeactivate() = 0;

	virtual void OnUpdate(float DeltaTime) = 0;
	virtual void OnRender() = 0;
	
	virtual EntityManager& GetManager() { return m_Manager; }
protected:
	EntityManager m_Manager;
	ScriptManager* m_ScriptManager;
	unsigned int m_EntitiesCount;
	
};



#endif