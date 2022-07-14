
#include "Material.h"

namespace RayCast {

	Material::Material()
	{
		m_Color = { 1.0f,1.0f,1.0f };
		m_Shininess = 1.f;
		Disable();
	}

	Material::Material(Texture* diffuseTexture, Texture* specularTexture, float shininess, glm::vec3 color)
		: m_iDiffuseTexture(diffuseTexture),
		m_iSpecularTexture(specularTexture),
		m_Shininess(shininess),
		m_Color(color)
	{
		Enable();
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

	void Material::AddDiffuseTexture(Texture* diffuse)
	{
		m_iDiffuseTexture = diffuse;
	}

	void Material::AddSpecularTexture(Texture* specular)
	{
		m_iSpecularTexture = specular;
	}

	bool& Material::IsActive()
	{
		return m_Active;
	}

	bool& Material::IsVisisble()
	{
		return m_Visibility;
	}

	void Material::Enable()
	{
		m_Active = true;
	}

	void Material::Disable()
	{
		m_Active = false;
	}

	float& Material::GetShininess()
	{
		return m_Shininess;
	}

	glm::vec3& Material::GetColor()
	{
		return m_Color;
	}

	void Material::SetUniforms(Shader& shader)
	{
		if (m_Active) {
			if (m_Visibility) {
				shader.use();

				m_iDiffuseTexture->bind(m_iDiffuseTexture->GetId());
				m_iSpecularTexture->bind(m_iSpecularTexture->GetId());

				if (m_Textured) {
					shader.setInt("material.diffuseTexture", m_iDiffuseTexture->GetId());
					shader.setInt("material.specularTexture", m_iSpecularTexture->GetId());
				}
				shader.setFloat("material.shininess", m_Shininess);
				shader.SetVec3("material.color", m_Color);
			}
		}
	}

}