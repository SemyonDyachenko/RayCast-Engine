#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Mesh.h"

#include "HeightmapGenerator.h"
#include "../OBJLoader.h"
#include "../../Core/Log.h"
#include "../stb_image.h"


#define TERRAIN_SIZE 800
#define VERTEX_COUNT 128
#define MAX_PIXEL_COLOR 256 * 256 * 256
#define MAX_HEIGHT 40


namespace RayCast {

	class RAYCAST_API Terrain
	{
	public:
		Terrain(unsigned int gridSizeX, unsigned int gridSizeZ);

		Mesh* GenerateMesh();

		Mesh* GenerateHeightMapMesh(std::string heightmapPath);


		void OnRender(Shader& shader);

		void SetGridSize(float gridSizeX, float gridSizeY) { m_GridSizeX = gridSizeX; m_GridSizeZ = gridSizeY; m_Mesh = GenerateMesh(); }

		void SetHeightMapFromResource(std::string path);

		Mesh& GetTerrainMesh() { return *m_Mesh; }

		bool& HeightMapUsed() { return heightMapUsed; }


		float& GetGridSizeX() { return m_GridSizeX; }
		float& GetGridSizeZ() { return m_GridSizeZ; }

	private:
		static float GetHeight(int x, int z, int image_width, int image_height, unsigned char* image_data, int numberChannels);
		static float GetHeight(int x, int z, HeightmapGenerator& generator);

		glm::vec3 CalculateNormal(int x, int z, HeightmapGenerator& generator);
	private:
		float X, Z;
		float m_GridSizeX;
		float m_GridSizeZ;
		Mesh* m_Mesh;

		float m_TerrainSize;
		float m_VertexCount;
		float m_MaxPixelColor;

		bool heightMapUsed = false;
	};

}

#endif