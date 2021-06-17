#include "LightPoint.h"

LightPoint::LightPoint() : m_Position({0.0f,0.0f,0.0f}), m_Power(1.f), m_Color(glm::vec3(1.f)), m_Constant(1.f), m_Linear(0.045f),m_Quadratic(0.0075f)
{
	
}

LightPoint::LightPoint(glm::vec3 position, float power, glm::vec3 color, float constant, float linear, float quadratic)
	: m_Position(position),
	m_Power(power),
	m_Color(color),
	m_Constant(constant),
	m_Linear(linear),
	m_Quadratic(quadratic)
{
	
}

void LightPoint::SetPosition(glm::vec3 position)
{
	m_Position = position;
}

void LightPoint::SetColor(glm::vec3 color)
{
	m_Color = color;
}

void LightPoint::SetPower(float power)
{
	m_Power = power;
}

glm::vec3 LightPoint::GetPosition()
{
	return m_Position;
}

void LightPoint::SetUniforms(Shader& shader)
{
	shader.use();

	shader.SetVec3("light.color", m_Color);
	shader.SetVec3("light.position", m_Position);
	shader.setFloat("light.power", m_Power);
	shader.setFloat("light.constant", m_Constant);
	shader.setFloat("light.linear", m_Linear);
	shader.setFloat("light.quadratic", m_Quadratic);
}
