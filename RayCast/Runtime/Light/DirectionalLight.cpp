#include "../../stdafx.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color)
	: m_Direction(direction), m_Ambient(ambient),m_Diffuse(diffuse),m_Specular(specular),m_Color(color)
{
}



void DirectionalLight::SetUniforms(Shader& shader)
{
	shader.use();

	shader.setBool("hasDirectionalLight", true);
	shader.SetVec3("dirLight.color", m_Color);
	shader.SetVec3("dirLight.direction", m_Direction);
	shader.SetVec3("dirLight.ambient", m_Ambient);
	shader.SetVec3("dirLight.diffuse", m_Diffuse);
	shader.SetVec3("dirLight.specular", m_Specular);
}
