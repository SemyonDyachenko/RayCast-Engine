#include "SceneHierarchy.h"


SceneHierarchy::SceneHierarchy(EditorScene& scene)
{
    m_CountObject = scene.GetObjectCount();
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

unsigned int SceneHierarchy::GetSelectedObject()
{
    return m_SelectedObject;
}

void SceneHierarchy::SetSelectedObject(int id)
{
    m_SelectedObject = id;
}

void SceneHierarchy::Update(float DeltaTime)
{
}

void SceneHierarchy::Render()
{
    std::map<int, std::string>::iterator it;

    ImGui::Begin("Scene Hierarchy");

    for (auto it = objects.begin(); it != objects.end(); it++) {

        ImGuiTreeNodeFlags flags = ((m_SelectedObject == it->first) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)it->first, flags,it->second.c_str());

        if (ImGui::IsItemClicked())
        {
            m_SelectedObject = it->first;
        }
    }

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        m_SelectedObject = -1;

    ImGui::End();
}
