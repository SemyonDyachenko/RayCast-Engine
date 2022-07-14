
#include "LightPoint.h"


namespace RayCast {
	LightPoint::LightPoint(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color, float constant, float linear, float quadratic)
		: m_Position(position), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Color(color), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
	{
	}

	void LightPoint::SetUniforms(Shader& shader)
	{
		shader.use();
		shader.setBool("hasPointLight", true);

		shader.SetVec3("light.lightColor", m_Color);
		shader.SetVec3("light.position", m_Position);
		shader.SetVec3("light.ambient", m_Ambient);
		shader.SetVec3("light.diffuse", m_Diffuse);
		shader.SetVec3("light.specular", m_Specular);
		shader.setFloat("light.constant", m_Constant);
		shader.setFloat("light.linear", m_Linear);
		shader.setFloat("light.quadratic", m_Quadratic);

	}

}