#include "Terrain.h"

namespace RayCast {

	Terrain::Terrain(unsigned int gridSizeX, unsigned int gridSizeZ)
		: m_GridSizeX(gridSizeX), m_GridSizeZ(gridSizeZ)
	{
		X = m_GridSizeX * TERRAIN_SIZE;
		Z = m_GridSizeZ * TERRAIN_SIZE;
		m_Mesh = GenerateMesh();
	}

	Mesh* Terrain::GenerateMesh()
	{
		auto* generator = new HeightmapGenerator();

		heightMapUsed = false;

		float count = VERTEX_COUNT * VERTEX_COUNT;
		std::vector<Vertex> finalVertices(count);
		std::vector<glm::fvec3> vertices(count);
		std::vector <glm::fvec3> normals(count);
		std::vector <glm::fvec2> texcoords(count);
		std::vector<GLuint> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));


		int index = 0;

		//GetHeight(j,i,*generator)

		for (size_t i = 0; i < VERTEX_COUNT; i++) {
			for (size_t j = 0; j < VERTEX_COUNT; j++) {
				glm::vec3 v = { j / (float)(VERTEX_COUNT - 1),GetHeight(j,i,*generator),i / (float)(VERTEX_COUNT - 1) };
				v.x *= m_GridSizeX;
				v.z *= m_GridSizeZ;
				v.x -= m_GridSizeX / 2.f;
				v.z -= m_GridSizeZ / 2.f;

				vertices[index] = v;
				normals[index] = CalculateNormal(j, i, *generator);

				finalVertices[index].position = vertices[index];
				finalVertices[index].normal = normals[index];
				finalVertices[index].texcoord = glm::vec2((float)j / ((float)VERTEX_COUNT - 1), (float)i / ((float)VERTEX_COUNT - 1));

				index++;
			}
		}

		int pointer = 0;
		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				int topLeft = (gz * VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}

		Mesh* finalMesh = new Mesh(finalVertices.data(), finalVertices.size(), indices.data(), indices.size());
		return finalMesh;
	}

	Mesh* Terrain::GenerateHeightMapMesh(std::string heightmapPath)
	{
		auto* generator = new HeightmapGenerator();

		heightMapUsed = true;

		int img_width, img_height;
		int nrChannels;
		unsigned char* image = stbi_load(heightmapPath.c_str(), &img_width, &img_height, &nrChannels, 0);


		float count = VERTEX_COUNT * VERTEX_COUNT;
		std::vector<Vertex> finalVertices(count);
		std::vector<glm::fvec3> vertices(count);
		std::vector <glm::fvec3> normals(count);
		std::vector <glm::fvec2> texcoords(count);
		std::vector<GLuint> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));


		int index = 0;

		for (size_t i = 0; i < VERTEX_COUNT; i++) {
			for (size_t j = 0; j < VERTEX_COUNT; j++) {
				glm::vec3 v = { j / (float)(VERTEX_COUNT - 1),(float)GetHeight(i, j, img_width, img_height, image, nrChannels),i / (float)(VERTEX_COUNT - 1) };
				v.x *= m_GridSizeX;
				v.z *= m_GridSizeZ;
				v.x -= m_GridSizeX / 2.f;
				v.z -= m_GridSizeZ / 2.f;

				vertices[index] = v;
				normals[index] = CalculateNormal(j, i, *generator);

				finalVertices[index].position = vertices[index];
				finalVertices[index].normal = normals[index];
				finalVertices[index].texcoord = glm::vec2((float)j / ((float)VERTEX_COUNT - 1), (float)i / ((float)VERTEX_COUNT - 1));

				index++;
			}
		}

		int pointer = 0;
		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				int topLeft = (gz * VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}

		Mesh* finalMesh = new Mesh(finalVertices.data(), finalVertices.size(), indices.data(), indices.size());
		return finalMesh;
	}

	float Terrain::GetHeight(int x, int z, int image_width, int image_height, unsigned char* image_data, int numberChannels)
	{
		if (x < 0 || x >= image_height || z < 0 || z >= image_height) {
			return 0.0f;
		}

		unsigned char* pixelOffset = image_data + (x + image_height * z) * numberChannels;
		unsigned char r = pixelOffset[0];
		unsigned char g = pixelOffset[1];
		unsigned char b = pixelOffset[2];

		float height = static_cast<float>(r);
		height -= 127.5;
		height /= 127.5;
		height *= MAX_HEIGHT;

		return height;
	}

	float Terrain::GetHeight(int x, int z, HeightmapGenerator& generator)
	{
		return generator.GenerateHeight(x, z);
	}

	glm::vec3 Terrain::CalculateNormal(int x, int z, HeightmapGenerator& generator)
	{
		float heightL = GetHeight(x - 1, z, generator);
		float heightR = GetHeight(x + 1, z, generator);
		float heightD = GetHeight(x, z - 1, generator);
		float heightU = GetHeight(x, z + 1, generator);

		glm::vec3 normal = { heightL - heightR,2.f,heightD - heightU };
		normal = glm::normalize(normal);
		return normal;
	}

	void Terrain::OnRender(Shader& shader) {

		glm::vec3 solidColor = { 1.0f,1.0f,1.0f };
		m_Mesh->SetSolidColor(solidColor);
		m_Mesh->OnRender(shader);
	}

	void Terrain::SetHeightMapFromResource(std::string path)
	{
		heightMapUsed = true;
		m_Mesh = GenerateHeightMapMesh(path);
	}


}