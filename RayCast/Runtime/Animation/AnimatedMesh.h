#ifndef ANIMATED_MESH_H
#define ANIMATED_MESH_H

#include <GL/glew.h>
#include <vector>

#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include "../Rendering/Shader.h"

#define MAX_BONE_INFLUENCE 4

struct AnimatedVertex {
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];

};

struct AnimatedTexture {
	GLint id;
	std::string type;
	std::string path;
};



class AnimatedMesh
{

public:
	AnimatedMesh(std::vector<AnimatedVertex> vertices,std::vector<unsigned int> indices,std::vector<AnimatedTexture> textures);

	void UseSolidColor(bool use);


	virtual ~AnimatedMesh();

	void OnRender(Shader& shader);

private:
	std::vector<AnimatedVertex> vertices;
	std::vector<unsigned int> indices;

	bool m_UseSolidColor = true;

	int m_verticesCount;
	int m_numberOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::mat4 ModelMatrix;

};


#endif

