#ifndef SHADOW_MAPPER_H
#define SHADOW_MAPPER_H

#include <glm.hpp>
#include <vector>
#include "../../Camera/Camera.h"
#include "../../Light/Light.h"

/*
struct ShadowProps {
	unsigned int TEXEL_SIZE = 1024;
	unsigned int depthMapTextureID;
	unsigned int depthMapRendererID;
	glm::mat4 ViewProjectionMatrix;
	float cascadeSplitFar;
	glm::vec3 frustumCorners[8];
};

class ShadowMapper
{
public:
	ShadowMapper() {}
	virtual ~ShadowMapper() {}

	void Init();

	void CalculateProjections(EditorCamera* camera, Light* light);
	void Bind(int index);
	void Unbind();

	void SetCascadesCount(unsigned int count);
	void SetCascadesResolution(unsigned int count);
	void SetShadowDistance(unsigned int dist);

	unsigned int GetShadowDistance();	
	void Clear();




public:
	unsigned int m_ShadowMapCascadeCount = 2;
	unsigned int TEXEL_SIZE = 1024;
	unsigned int SHADOW_DISTANCE = 150;

	std::vector<ShadowProps> cascades;

	float CascadeSplits[3];

private:
	bool m_Initialized = false;
	bool CascadesSplitsCount = false;
};
*/
#endif