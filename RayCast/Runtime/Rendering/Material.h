#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <glm.hpp>

#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,GLint diffuseTexture,GLint specularTexture,glm::vec3 color);
	virtual ~Material();

	glm::vec3 GetAmbient();
	glm::vec3 GetSpecular();
	glm::vec3 GetDiffuse();

	void SetUniforms(Shader& shader);

private:
	glm::vec3 m_vAmbient;
	glm::vec3 m_vDiffuse;
	glm::vec3 m_vSpecular;
	glm::vec3 m_Color;
	float m_Shininess;
	GLint m_iDiffuseTexture;
	GLint m_iSpecularTexture;
	
};


#endif