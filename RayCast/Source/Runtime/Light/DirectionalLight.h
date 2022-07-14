#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm.hpp>
#include "../Rendering/Shader.h"


class DirectionalLight
{
public:

	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color);

	virtual ~DirectionalLight() = default;

	void SetDirection(glm::vec3 direction) { m_Direction = direction; }
	void SetColor(glm::vec3 color) { m_Color = color; }

	void SetAmbient(glm::vec3 ambient) { m_Ambient = ambient; }
	void SetSpecular(glm::vec3 specular) { m_Specular = specular; }
	void SetDiffuse(glm::vec3 diffuse) { m_Diffuse = diffuse; }

	glm::vec3& GetColor() { return m_Color; }
	glm::vec3& GetDiffuse() { return m_Diffuse; }
	glm::vec3& GetAmbient() { return m_Ambient; }
	glm::vec3& GetSpecular() { return m_Specular; }
	glm::vec3& GetDirection() { return m_Direction; }

	void SetUniforms(Shader& shader);

private:
	glm::vec3 m_Color;

	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;

	glm::vec3 m_Direction;
};

#endif