#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/GLU.h>
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
	Mesh(Vertex* vertices, int verticesCount, GLuint* indices, int indicesCount);

	//void UpdateModelMatrix(glm::mat4 ModelMatrix);
	
	virtual ~Mesh();

	void OnRender(Shader & shader);

private:
	Vertex * vertices;
	std::vector<unsigned int> indices;

	
	int m_verticesCount;
	int m_numberOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;


};


#endif
