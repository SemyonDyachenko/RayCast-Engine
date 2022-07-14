#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Mesh.h"

#define TERRAIN_SIZE 800
#define VERTEX_COUNT 128
#define MAX_PIXEL_COLOR 256 * 256 * 256
#define MAX_HEIGHT 40

class Terrain
{
public:
	Terrain(unsigned int gridSizeX, unsigned int gridSizeZ);

	Mesh* GenerateMesh();

	float GetHeight(int x, int z, int image_width,int image_height,unsigned char* image_data, int numberChannels);

	void OnRender(Shader& shader);

private:
	float X, Z;
	unsigned int  m_GridSizeX;
	unsigned int m_GridSizeZ;
	Mesh* m_Mesh;

	float m_TerrainSize;
	float m_VertexCount;
	float m_MaxPixelColor;
};

#endif