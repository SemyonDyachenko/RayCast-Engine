#ifndef PBR_MATERIAL_H
#define PBR_MATERIAL_H

#include "../Texture.h"
#include "../Shader.h"
#include "../../Core/Log.h"

#include "MaterialController.h"

class PBRMaterial
{
public:
	PBRMaterial() { m_AlbedoMap = nullptr; m_NormalMap = nullptr; m_MetallicMap = nullptr; m_RoughnessMap = nullptr; m_AoMap = nullptr; }
	PBRMaterial(Texture* albedo, Texture* normal, Texture* metallic, Texture* roughness, Texture* ao);

	void Apply(std::string path);

	void ApplyAlbedoMap(Texture* map) { m_AlbedoMap = map; }
	void ApplyNormalMap(Texture* map) { m_NormalMap = map; }
	void ApplyMetallicMap(Texture* map) { m_MetallicMap = map; }
	void ApplyRoughnessMap(Texture* map) { m_RoughnessMap = map; }
	void ApplyAoMap(Texture* map) { m_AoMap = map; }
	
	virtual ~PBRMaterial();

	bool IsActive() const;

	void SetUniforms(Shader & shader);

	std::string GetName() {
		if (m_Path.length() > 0) {
			std::filesystem::path path = m_Path;
			std::string name = path.stem().string();

			return name;
		}
		else {
			return "";
		}
	}

	std::string& GetPath() { return m_Path; }

public:
	Texture* m_AlbedoMap;
	Texture* m_NormalMap;
	Texture* m_MetallicMap;
	Texture* m_RoughnessMap;
	Texture* m_AoMap;

	bool m_Active = false;

	std::string m_Path;
};



#endif