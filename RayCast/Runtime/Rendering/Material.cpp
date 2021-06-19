#include "Material.h"



Material::Material(Texture* diffuseTexture, Texture* specularTexture, float shininess,glm::vec3 color)
	: m_iDiffuseTexture(diffuseTexture),
	m_iSpecularTexture(specularTexture),
	m_Shininess(shininess),
	m_Color(color)
{
}

Material::~Material()
{
}

Texture& Material::GetDiffuseTexture()
{
	return *m_iDiffuseTexture;
}

Texture& Material::GetSpecularTexture()
{
	return *m_iSpecularTexture;
}

float& Material::GetShininess()
{
	return m_Shininess;
}

glm::vec3& Material::GetColor()
{
	return m_Color;
}

void Material::SetUniforms(Shader & shader)
{
	shader.use();

	m_iDiffuseTexture->bind(m_iDiffuseTexture->GetId());
	m_iSpecularTexture->bind(m_iSpecularTexture->GetId());

	shader.setInt("material.diffuseTexture", m_iDiffuseTexture->GetId());
	shader.setInt("material.specularTexture",  m_iSpecularTexture->GetId());	
	shader.setFloat("material.shininess", m_Shininess);
	shader.SetVec3("material.color",  m_Color);	
}
