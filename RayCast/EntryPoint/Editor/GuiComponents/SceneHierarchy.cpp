#include "SceneHierarchy.h"


SceneHierarchy::SceneHierarchy(EditorScene& scene)
{
    m_Scene = &scene;
}

void SceneHierarchy::PushObject(unsigned int id, std::string name, EditorScene& scene)
{
    auto it = objects.find(id);

    if (it == objects.end()) {
        objects.insert({ id,name });
        m_CountObject = scene.GetEntitiesCount();
    }
    else {
        std::cout << "ERROR: Object with id already created. (SceneHierarchy.cpp, PushObject())" << "\n";
    }
}

void SceneHierarchy::DeleteObject(unsigned int id, EditorScene& scene)
{
    auto it = objects.find(id);

    if (it != objects.end()) {
        objects.erase(it);
        m_CountObject = scene.GetEntitiesCount();
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

void SceneHierarchy::SetSelectedObject(unsigned int id)
{
    m_SelectedObject = id;
}

void SceneHierarchy::DeleteNodeById(unsigned int id)
{
    objects.erase(id);
}

void SceneHierarchy::Update(float DeltaTime)
{
}

void SceneHierarchy::Render(EditorScene& editorScene)
{
    std::map<int, std::string>::iterator it;
    m_CountObject = editorScene.GetEntitiesCount();

    ImGui::Begin("Scene Hierarchy");

    for (auto& entity : m_Scene->GetManager().GetEntities()) {

        std::string name = entity->GetName();

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity->GetId(), flags, name.c_str());

        if (ImGui::IsItemClicked())
        {
            m_SelectedEntity = *entity;
            HasSelected = true;
        }

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete))) {
            if (entity->GetId() == m_SelectedEntity.GetId()) {
                m_SelectedEntity = {};
                HasSelected = false;

                std::cout << entity->GetId() << "\n";

                m_Scene->DeleteEntity(entity->GetId());
                editorScene.RecalculateEntitiesCount();
               
            }
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity")) {
                if (entity->GetId() == m_SelectedEntity.GetId()) {
                    m_SelectedEntity = {};
                    HasSelected = false;
                }

                m_Scene->DeleteEntity(entity->GetId());
                editorScene.RecalculateEntitiesCount();
          
            }
            ImGui::EndPopup();
        }
    

    if (opened)
    {
        ImGui::TreePop();
    }   

    }

  /*  for (auto it = objects.begin(); it != objects.end();) {

        ImGuiTreeNodeFlags flags = ((m_SelectedObject == it->first) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)it->first, flags,it->second.c_str());

        if (ImGui::IsItemClicked())
        {
            m_SelectedObject = it->first;
        }

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete))) {
            if (it->first == m_SelectedObject) {
                m_SelectedObject = -1;

            editorScene.DeleteEntity(it->first);
            editorScene.RecalculateEntitiesCount();
 

                objects.erase(it);
                it = objects.begin();
            }
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity")) {
                if (it->first == m_SelectedObject) 
                    m_SelectedObject = -1;

                editorScene.DeleteEntity(it->first);

                objects.erase(it);
                it = objects.begin();

          
            }
            
               

            ImGui::EndPopup();

        }
        if (opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = ImGui::TreeNodeEx((void*)it->first, flags, it->second.c_str());
            if (opened)
                ImGui::TreePop();
            ImGui::TreePop();
        }

        if(it != objects.end()) 
            it++;
    }
    */
    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
        HasSelected = false;
        m_SelectedEntity = {};
    }
        

    ImGui::End();
}

void SceneHierarchy::EntityNode(std::unique_ptr<Entity> entity)
{
   
}
