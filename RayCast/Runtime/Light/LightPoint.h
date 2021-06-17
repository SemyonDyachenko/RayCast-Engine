#ifndef LIGHT_POINT_H
#define LIGHT_POINT_H

#include <GL/glew.h>
#include <glm.hpp>
#include "../Rendering/Shader.h"

class LightPoint
{
public:
	LightPoint();

	LightPoint(glm::vec3 position,float power = 1.f,glm::vec3 color = glm::vec3(1.f),float constant = 1.f,float linear = 0.045f,float quadratic = 0.0075f);

	virtual ~LightPoint() = default;

	void SetPosition(glm::vec3 position);
	void SetColor(glm::vec3 color);
	void SetPower(float power);

	glm::vec3 GetPosition();

	void SetUniforms(Shader& shader);

private:
	float m_Power;
	glm::vec3 m_Color;
	glm::vec3 m_Position;
	float m_Constant;
	float m_Linear;
	float m_Quadratic;

};


#endif