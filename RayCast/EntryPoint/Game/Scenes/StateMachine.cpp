#include "../../../stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine() : m_Scenes(0),m_currentScene(0)
{

}

void StateMachine::Update(float DeltaTime)
{
    if (m_currentScene)
        m_currentScene->OnUpdate(DeltaTime);
}

void StateMachine::Render()
{
    if (m_currentScene)
        m_currentScene->OnRender();
}
    
unsigned int StateMachine::Add(std::shared_ptr<Scene> scene)
{
    auto insertedScene = m_Scenes.insert(std::make_pair(insertedSceneID, scene));

    insertedSceneID++;

    insertedScene.first->second->OnCreate();

    return insertedSceneID - 1;
}

void StateMachine::SwitchToScene(unsigned int id)
{
    auto it = m_Scenes.find(id);

    if (it != m_Scenes.end()) {
        if (m_currentScene) {
            m_currentScene->OnDeactivate();
        }

        m_currentScene = it->second;

        m_currentScene->OnActivate();
    }
}

void StateMachine::RemoveScene(unsigned int id)
{
    auto it = m_Scenes.find(id);

    if (it != m_Scenes.end()) {
        if (m_currentScene == it->second) {
            m_currentScene = nullptr;
        }
        it->second->OnDestroy();

        m_Scenes.erase(it);
    }
}
