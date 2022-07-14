#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "Scene.h"
#include <memory>
#include <unordered_map>



class StateMachine
{
public:
	StateMachine();

	void Update(float DeltaTime);
	void Render();

	unsigned int Add(std::shared_ptr<Scene> scene);

	void SwitchToScene(unsigned int id);

	void RemoveScene(unsigned int id);

private:
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> m_Scenes;

	std::shared_ptr<Scene> m_currentScene;

	unsigned int insertedSceneID;

};

#endif