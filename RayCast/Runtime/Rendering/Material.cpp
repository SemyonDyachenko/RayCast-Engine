#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture,glm::vec3 color)
	: m_vAmbient(ambient),
	 m_vDiffuse(diffuse),
	 m_vSpecular(specular),
	 m_iDiffuseTexture(diffuseTexture),
	 m_iSpecularTexture(specularTexture),
	 m_Color(color)
{

}

Material::~Material()
{
}

glm::vec3 Material::GetAmbient()
{
	return m_vAmbient;
}

glm::vec3 Material::GetSpecular()
{
	return m_vSpecular;
}

glm::vec3 Material::GetDiffuse()
{
	return m_vDiffuse;
}

void Material::SetUniforms(Shader & shader)
{
	shader.SetVec3("material.ambient", m_vAmbient);
	shader.SetVec3("material.diffuse", m_vDiffuse);
	shader.SetVec3("material.specular", m_vSpecular);
	shader.setInt("material.diffuseTexture",  m_iDiffuseTexture);
	shader.setInt("material.specularTexture",  m_iSpecularTexture);	
	shader.SetVec3("material.color",  m_Color);	
}
