#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

#include <glm.hpp>
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 color;
	glm::vec3 normal;

	//int m_BoneIDs[MAX_BONE_INFLUENCE];
	//float m_Weights[MAX_BONE_INFLUENCE];
	
};



class Mesh
{	

public:
	Mesh(Vertex* vertices, int verticesCount, GLuint* indices, int indicesCount,std::string filename = "");

	//void UpdateModelMatrix(glm::mat4 ModelMatrix);
	
	virtual ~Mesh();

	void SetSolidColor(glm::vec3& color);

	void OnRender(Shader & shader);

	std::string& GetFilename() { return m_Filename; }

	glm::vec3& GetSolidColor() { return m_SolidColor; }

private:
	Vertex * vertices;
	std::vector<unsigned int> indices;

	std::string m_Filename;

	glm::vec3 m_SolidColor = { 1.0f,1.0f,1.0f };
	
	int m_verticesCount;
	int m_numberOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;


};


#endif
