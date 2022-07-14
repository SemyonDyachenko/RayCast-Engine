#include "PBRMaterial.h"


PBRMaterial::PBRMaterial(Texture* albedo, Texture* normal, Texture* metallic, Texture* roughness, Texture* ao)
	: m_AlbedoMap(albedo),
	m_NormalMap(normal),
	m_MetallicMap(metallic),
	m_RoughnessMap(roughness),
	m_AoMap(ao)
{

}

void PBRMaterial::Apply(std::string path)
{
	if (path.length() > 0)
	{
		MaterialStructure structure = MaterialController::Deserailize(path);

		m_AlbedoMap = new Texture(structure.AlbedoColor.c_str());
		m_NormalMap = new Texture(structure.NormalMap.c_str());
		m_MetallicMap = new Texture(structure.MetallicMap.c_str());
		m_RoughnessMap = new Texture(structure.RoughnessMap.c_str());
		m_AoMap = new Texture(structure.AoMap.c_str());

		m_Path = path;
	}
	else
	{
		ENGINE_ERROR("Error loading material from " + path);
	}
}

PBRMaterial::~PBRMaterial()
{
	delete m_AlbedoMap;
	delete m_NormalMap;
	delete m_RoughnessMap;
	delete m_MetallicMap;
	delete m_AoMap;
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
		shader.setBool("useTextureMapping", true);

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
		shader.use();
		shader.setBool("useTextureMapping", false);
		ENGINE_ERROR("Texture maps for material not found! (PBRMaterial.cpp)");
	}
}
