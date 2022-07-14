#include "Light.h"

Light::Light(unsigned int id,LightMode mode)
{
    m_LightID = id;
    m_Mode = mode;
    m_Position = { 0.0f,0.0f,0.0f };
    m_AmbientColor = { 1.0f,1.0f,1.0f };
  
}

Light::Light(unsigned int id,LightMode mode, glm::vec3 position, glm::vec3 ambientColor)
{
    m_LightID = id;
    m_Mode = mode;
    m_Position = position;
    m_AmbientColor = ambientColor;
}

Light::~Light()
{
}

void Light::SetPosition(glm::vec3 position)
{
    m_Position = position;
}

void Light::SetAmbientColor(glm::vec3 color)
{
    m_AmbientColor = color;
}

void Light::SetIntensivity(float intensivity)
{
    m_Intensivity = intensivity;
}

void Light::SetUniforms(Shader& shader)
{
    shader.use();

    switch (m_Mode)
    {
    case DIRECTIONAL_LIGHT:
        shader.setInt("lights[" + std::to_string(m_LightID) + "].mode", 0);
        break;
    case SPOTLIGHT:
        shader.setInt("lights[" + std::to_string(m_LightID) + "].mode", 1);
        break;
    case POINT_LIGHT:
        shader.setInt("lights[" + std::to_string(m_LightID) + "].mode", 2);
        break;
    default:
        break;
    }

    shader.setInt("lights[" + std::to_string(m_LightID) + "].intensities", static_cast<int>(m_Intensivity));
    shader.SetVec3("lights[" + std::to_string(m_LightID) + "].position", m_Position);
    shader.SetVec3("lights[" + std::to_string(m_LightID) + "].ambientColor", m_AmbientColor);
}

glm::vec3& Light::GetPoisition() 
{
    return m_Position;
}

glm::vec3& Light::GetAmbientColor() 
{
    return m_AmbientColor;
}
