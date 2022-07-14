#include "Terrain.h"
#include "../OBJLoader.h"
#include "../../Core/Log.h"
#include "../stb_image.h"


Terrain::Terrain(unsigned int gridSizeX, unsigned int gridSizeZ)
	: m_GridSizeX(gridSizeX), m_GridSizeZ(gridSizeZ)
{
	X = m_GridSizeX * TERRAIN_SIZE;
	Z = m_GridSizeZ * TERRAIN_SIZE;
	m_Mesh = GenerateMesh();
}

Mesh* Terrain::GenerateMesh()
{
	int img_width, img_height;
	int nrChannels;
	unsigned char* image = stbi_load("resources/images/heightmaps/heightmap.png", &img_width, &img_height, &nrChannels, 0);

	float count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<Vertex> finalVertices(count);
	std::vector<glm::fvec3> vertices(count);
	std::vector <glm::fvec3> normals(count);
	std::vector <glm::fvec2> texcoords(count);
	std::vector<GLuint> indices;


	int index = 0;

	for (size_t i = 0; i < VERTEX_COUNT; i++) {
		for (size_t j = 0; j < VERTEX_COUNT; j++) {
			glm::vec3 v = { i / (float)VERTEX_COUNT,(float)GetHeight(i, j, img_width, img_height, image, nrChannels),j / (float)VERTEX_COUNT };
			v.x *= m_GridSizeX;
			v.z *= m_GridSizeZ;
			v.x -= m_GridSizeX / 2.f;
			v.z -= m_GridSizeZ / 2.f;

			vertices[index] = v;
			normals[index] = glm::vec3(0.0f, 1.0f, 0.0f);

			if ((i + 1 % (int)VERTEX_COUNT) != 0 && j + 1 < VERTEX_COUNT) {
				int t1 = index + (int)VERTEX_COUNT + 1;
				int t2 = index + (int)VERTEX_COUNT;
				int t3 = index;
				int t4 = index;
				int t5 = index + 1;
				int t6 = index + (int)VERTEX_COUNT + 1;

				indices.push_back(t1);
				indices.push_back(t2);
				indices.push_back(t3);
				indices.push_back(t4);
				indices.push_back(t5);
				indices.push_back(t6);
			}

			finalVertices[index].position = vertices[index];
			finalVertices[index].normal = normals[index];
			finalVertices[index].texcoord =glm::vec2((float)j/((float)VERTEX_COUNT-1),(float)i/((float)VERTEX_COUNT-1));

			index++;
		}
	}

	Mesh* finalMesh = new Mesh(finalVertices.data(), finalVertices.size(), indices.data(), indices.size());
	return finalMesh;
}

float Terrain::GetHeight(int x, int z, int image_width, int image_height,unsigned char* image_data,int numberChannels)
{
	if (x < 0 || x >= image_height || z < 0 || z >= image_height) {
		return 0.0f;
	}

	unsigned char* pixelOffset = image_data + (x + image_height * z) * numberChannels;
	unsigned char r = pixelOffset[0];
	unsigned char g = pixelOffset[1];
	unsigned char b = pixelOffset[2];

	float height = (float)r;
	height -= 127.5;
	height /= 127.5;
	height *= MAX_HEIGHT;
	
	return height;
}

void Terrain::OnRender(Shader& shader) {

	glm::vec3 solidColor = { 1.0f,1.0f,1.0f };
	m_Mesh->SetSolidColor(solidColor);
	m_Mesh->OnRender(shader);
}