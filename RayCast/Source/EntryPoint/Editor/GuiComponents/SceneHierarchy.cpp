#include "stdafx.h"
#include "SceneHierarchy.h"


SceneHierarchy::SceneHierarchy(EditorScene& scene)
{
    m_Scene = &scene;
    m_CountObject = scene.GetEntitiesCount();
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
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    bool open_ptr = true;
    ImGui::Begin("Scene Hierarchy",&open_ptr,window_flags);

    ImGuiTreeNodeFlags camera_flags =  ImGuiTreeNodeFlags_OpenOnArrow;

    bool camera = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)88543223, camera_flags, "Main Camera");

    if (camera)
    {
        ImGui::TreePop();
    }


    for (auto& entity : m_Scene->GetManager().GetEntities()) {
        if (entity) {
            std::string name = entity->GetName();

            ImGuiTreeNodeFlags flags = ((entity->GetId() == m_SelectedEntity.GetId() && HasSelected) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity->GetId(), flags, entity->GetComponent<TagComponent>().tag.c_str());

            if (ImGui::IsItemClicked())
            {
                m_SelectedEntity = *entity;
                HasSelected = true;
            }

            bool entityDeleted = false;
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete))) {
                if (entity->GetId() == m_SelectedEntity.GetId()) {
                    m_SelectedEntity = {};
                    HasSelected = false;
                    entityDeleted = true;
                }

            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity")) {
                    if (entity->GetId() == m_SelectedEntity.GetId()) {
                        m_SelectedEntity = {};
                        HasSelected = false;
                    }
                    entityDeleted = true;

                }
                ImGui::EndPopup();
            }


            if (opened)
            {
                if (entity->HasComponent<TagComponent>()) {
                    auto& tag = entity->GetComponent<TagComponent>();

                    if(ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId()+231), camera_flags, "Tag Component")) {
                        ImGui::Text(tag.tag.c_str());

                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<TransformComponent>()) {
                    auto& transform = entity->GetComponent<TransformComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 232), camera_flags, "Transform Component")) {
                        

                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<MeshComponent>()) {
                    auto& meshComponent = entity->GetComponent<MeshComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 233), camera_flags, "Mesh Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<MaterialComponent>()) {
                    auto& material = entity->GetComponent<MaterialComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 234), camera_flags, "Material Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<DirectionalLightComponent>()) {
                    auto& dirLight = entity->GetComponent<DirectionalLightComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 235), camera_flags, "Direction Light Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<LightPointComponent>()) {
                    auto& lightPoint = entity->GetComponent<LightPointComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 236), camera_flags, "Light Point Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<BoxColliderComponent>()) {
                    auto& boxCollider = entity->GetComponent<BoxColliderComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 237), camera_flags, "Box Collider Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<CircleColliderComponent>()) {
                    auto& CircleCollider = entity->GetComponent<CircleColliderComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 237), camera_flags, "Circle Collider Component")) {
                        ImGui::TreePop();
                    }

                }

                if (entity->HasComponent<RigidBodyComponent>()) {
                    auto& rigidBody = entity->GetComponent<RigidBodyComponent>();

                    if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity->GetId() + 238), camera_flags, "RigidBody Component")) {
                        ImGui::TreePop();
                    }

                }




                

                ImGui::TreePop();
            }

            if (entityDeleted) {

                m_Scene->DeleteEntity(entity->GetId());
                m_Scene->RecalculateEntitiesCount();
            }

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

    if (ImGui::BeginPopupContextWindow(0,1,false))
    {
        if (ImGui::MenuItem("Create Entity")) {
              
            auto& entity = m_Scene->CreateEntity(m_Scene->GetEntitiesCount(), "New Entity");
            m_Scene->RecalculateEntitiesCount();

        }
        ImGui::EndPopup();
    }

        

    ImGui::End();
}

void SceneHierarchy::EntityNode(std::unique_ptr<Entity> entity)
{
   
}
