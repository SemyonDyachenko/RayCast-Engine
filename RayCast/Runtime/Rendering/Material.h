#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <glm.hpp>

#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(Texture * diffuseTexture,Texture * specularTexture,float shininess,glm::vec3 color);
	virtual ~Material();

	Texture& GetDiffuseTexture();
	Texture& GetSpecularTexture();
	
	float& GetShininess();

	glm::vec3& GetColor();

	void SetUniforms(Shader& shader);

private:
	glm::vec3 m_Color;
	float m_Shininess;
	Texture* m_iDiffuseTexture;
	Texture* m_iSpecularTexture;
	
};


#endif