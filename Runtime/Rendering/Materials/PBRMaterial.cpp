#include "PBRMaterial.h"

namespace RayCast {


	PBRMaterial::PBRMaterial(Texture* albedo, Texture* normal, Texture* metallic, Texture* roughness, Texture* ao)
		: m_AlbedoMap(albedo),
		m_NormalMap(normal),
		m_MetallicMap(metallic),
		m_RoughnessMap(roughness),
		m_AoMap(ao)
	{

	}

	PBRMaterial::~PBRMaterial()
	{

	}

	bool PBRMaterial::IsActive() const
	{
		if (m_AlbedoMap && m_NormalMap && m_MetallicMap && m_RoughnessMap && m_AoMap) {
			return true;
		}
		else
		{
			return false;
		}
	}

	void PBRMaterial::SetUniforms(Shader& shader)
	{
		if (m_AlbedoMap && m_NormalMap && m_MetallicMap && m_RoughnessMap && m_AoMap) {

			shader.use();

			m_AlbedoMap->bind();
			m_NormalMap->bind();
			m_MetallicMap->bind();
			m_RoughnessMap->bind();
			m_AoMap->bind();

			shader.setInt("material.albedoMap", m_AlbedoMap->GetId());
			shader.setInt("material.normalMap", m_NormalMap->GetId());
			shader.setInt("material.metallicMap", m_MetallicMap->GetId());
			shader.setInt("material.roughnessMap", m_RoughnessMap->GetId());
			shader.setInt("material.aoMap", m_AoMap->GetId());
		}
		else
		{
			ENGINE_ERROR("Texture maps for material not found! (PBRMaterial.cpp)");
		}
	}


}