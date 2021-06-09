#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture)
	: m_vAmbient(ambient),
	 m_vDiffuse(diffuse),
	 m_vSpecular(specular),
	 m_iDiffuseTexture(diffuseTexture),
	 m_iSpecularTexture(specularTexture)

{

}

Material::~Material()
{
}

void Material::SetUniforms(Shader & shader)
{
	shader.SetVec3("material.ambient", m_vAmbient);
	shader.SetVec3("material.diffuse", m_vDiffuse);
	shader.SetVec3("material.specular", m_vSpecular);
	shader.setInt("material.diffuseTexture",  m_iDiffuseTexture);
	shader.setInt("material.specularTexture",  m_iSpecularTexture);	
}
