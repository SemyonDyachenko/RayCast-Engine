#include "SceneHierarchy.h"

SceneHierarchy::SceneHierarchy()
{
    m_CountObject = 0;
}

void SceneHierarchy::PushObject(unsigned int id, std::string name)
{
    auto it = objects.find(id);

    if(it == objects.end()) {
        objects.insert({ id,name });
        m_CountObject++;
    }
    else {
        std::cout << "ERROR: Object with id already created. (SceneHierarchy.cpp, PushObject())" << "\n";
    }
}

void SceneHierarchy::DeleteObject(unsigned int id)
{
    auto it = objects.find(id);

    if (it != objects.end()) {
        objects.erase(it);
        m_CountObject--;
    }
    else {
        std::cout << "ERROR: Object don't created. (SceneHierarchy.cpp, DeleteObject())" << "\n";
    }
}

std::map<unsigned int, std::string> SceneHierarchy::GetObjects()
{
    return objects;
}

unsigned int SceneHierarchy::GetObjectsCount()
{
    return m_CountObject;
}

void SceneHierarchy::Update(float DeltaTime)
{
}

void SceneHierarchy::Render()
{
    std::map<int, std::string>::iterator it;

    ImGui::Begin("Scene Hierarchy");

    for (auto it = objects.begin(); it != objects.end(); it++) {
        ImGui::Text(it->second.c_str());
    }

    ImGui::End();
}
