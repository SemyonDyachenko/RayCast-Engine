#include "EditorSceneObject.h"


EditorSceneObject::EditorSceneObject(int id, std::string name, std::string type)
{
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Scaling = 0.0f;

    m_Material = nullptr;
    m_Name = name;
    m_Type = type;
    Id = id;

    if (m_Type == "static") {
        m_AnimatedModel = nullptr;
    }
}

EditorSceneObject::~EditorSceneObject()
{
    if (m_Meshes.size() != 0) {
        for (Mesh* mesh : m_Meshes) {
            delete mesh;
        }
    }

    if (m_Textures.size() != 0) {
        for (Texture* texture : m_Textures) {
            delete texture;
        }
    }
}

void EditorSceneObject::Update(float DeltaTime)
{
}

void EditorSceneObject::Render(Shader * shader)
{
    if (m_Type == "static") {
        if (m_Meshes.size() != 0) {
            for (size_t i = 0; i < m_Textures.size(); i++)
                m_Textures[i]->bind(m_Textures[i]->GetId());
        }

        if (m_Meshes.size() != 0) {
            for (size_t i = 0; i < m_Meshes.size(); i++)
                m_Meshes[i]->OnRender(*shader);
        }
    }
    else {
        if (m_AnimatedModel != nullptr)
            m_AnimatedModel->Draw(*shader);
    }
}

void EditorSceneObject::AddMesh(Mesh* mesh)
{
    if (m_Type == "static") {
        m_Meshes.push_back(mesh);
    }
}

void EditorSceneObject::AddTexture(Texture* texture)
{
    m_Textures.push_back(texture);
}

void EditorSceneObject::AddMaterial(Material* material)
{
    if(m_Material == nullptr)
        m_Material = material;
}

AnimatedModel EditorSceneObject::AddAnimatedModel(AnimatedModel* model)
{
    if (m_Type == "dynamic") {
        m_AnimatedModel = model;
    }
    else {
        std::cout << "Animated Model is not available for static type object (EditorSceneObject.cpp)";
    }
}

void EditorSceneObject::SetPosition(glm::vec3 position)
{
    m_Position = position;
}

void EditorSceneObject::SetRotation(glm::vec3 rotation)
{
    m_Rotation = rotation;
}

void EditorSceneObject::SetScale(float scale)
{
    m_Scaling = scale;
}

glm::vec3& EditorSceneObject::GetPosition()
{
    return m_Position;
}

glm::vec3& EditorSceneObject::GetRotation()
{
    return m_Rotation;
}

float& EditorSceneObject::GetScale()
{
    return m_Scaling;
}

std::string& EditorSceneObject::GetType() 
{
    return m_Type;
}

std::string& EditorSceneObject::GetName() 
{
    return m_Name;
}

unsigned int EditorSceneObject::GetId()
{
    return Id;
}
