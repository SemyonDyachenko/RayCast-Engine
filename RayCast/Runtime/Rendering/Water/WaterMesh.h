#ifndef WATER_MESH_H
#define WATER_MESH_H

#include <vector>

#include "WaterTile.h"
#include "../Shader.h"

#include "../Mesh.h"

#include "../../Camera/Camera.h"

#include "../OBJLoader.h"

class WaterMesh
{
public:
	WaterMesh(std::vector<WaterTile*> waterSurface);

	virtual ~WaterMesh() = default;

	void AddReflectionAndRefractionTextures(int reflectionId,int refractionId);

	void Render(EditorCamera* camera);
public:
	Shader* m_WaterShader;

private:
	Mesh* m_Mesh;
	std::vector<WaterTile*> m_WaterSurface;

	int m_ReflectionTexID, m_RefractionTexID;
};

#endif