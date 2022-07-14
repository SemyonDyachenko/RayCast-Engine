#ifndef LIGHT_POINT_H
#define LIGHT_POINT_H

#include <glad/glad.h>
#include <glm.hpp>
#include "../Rendering/Shader.h"

class LightPoint
{
public:

	LightPoint(glm::vec3 position,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular, glm::vec3 color,float constant = 1.0,float linear = 0.045f,float quadratic = 0.0075f);

	virtual ~LightPoint() = default;

	void SetPosition(glm::vec3 position) { m_Position = position; }
	void SetColor(glm::vec3 color) { m_Color = color; }

	void SetAmbient(glm::vec3 ambient) { m_Ambient = ambient; }
	void SetSpecular(glm::vec3 specular) { m_Specular = specular; }
	void SetDiffuse(glm::vec3 diffuse) { m_Diffuse = diffuse; }

	glm::vec3 & GetColor() { return m_Color; }
	glm::vec3 &GetPosition() { return m_Position; }
	glm::vec3& GetDiffuse() { return m_Diffuse; }
	glm::vec3& GetAmbient() { return m_Ambient; }
	glm::vec3& GetSpecular() { return m_Specular; }

	float& GetConstant() { return m_Constant; }
	float& GetLinear() { return m_Linear; }
	float& GetQuadratic() { return m_Quadratic; }

	void SetUniforms(Shader& shader);

private:
	glm::vec3 m_Color;
	glm::vec3 m_Position;

	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;

	float m_Constant;
	float m_Linear;
	float m_Quadratic;
};


#endif