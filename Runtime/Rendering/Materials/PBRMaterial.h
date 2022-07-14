#ifndef PBR_MATERIAL_H
#define PBR_MATERIAL_H

#include "../Texture.h"
#include "../Shader.h"
#include "../../Core/Log.h"

namespace RayCast {

	class RAYCAST_API PBRMaterial
	{
	public:
		PBRMaterial() { m_AlbedoMap = nullptr; m_NormalMap = nullptr; m_MetallicMap = nullptr; m_RoughnessMap = nullptr; m_AoMap = nullptr; }
		PBRMaterial(Texture* albedo, Texture* normal, Texture* metallic, Texture* roughness, Texture* ao);

		void ApplyAlbedoMap(Texture* map) { m_AlbedoMap = map; }
		void ApplyNormalMap(Texture* map) { m_NormalMap = map; }
		void ApplyMetallicMap(Texture* map) { m_MetallicMap = map; }
		void ApplyRoughnessMap(Texture* map) { m_RoughnessMap = map; }
		void ApplyAoMap(Texture* map) { m_AoMap = map; }

		virtual ~PBRMaterial();

		bool IsActive() const;

		void SetUniforms(Shader& shader);
	public:
		Texture* m_AlbedoMap;
		Texture* m_NormalMap;
		Texture* m_MetallicMap;
		Texture* m_RoughnessMap;
		Texture* m_AoMap;

		bool m_Active = false;
	};


}


#endif