
#ifndef LIGHT_H
#define LIGHT_H

#include "../Rendering/Shader.h"

enum LightMode {
	DIRECTIONAL_LIGHT = 0,
	SPOTLIGHT =1,
	POINT_LIGHT =2,
};

class Light
{
public:
	Light(unsigned int id,LightMode mode);
	Light(unsigned int id,LightMode mode, glm::vec3 position, glm::vec3 ambientColor = {1.0f,1.0,1.0f});
	~Light();

	void SetPosition(glm::vec3 position);
	void SetAmbientColor(glm::vec3 color);
	void SetIntensivity(float intensivity);

	void SetMode(LightMode mode) { m_Mode = mode; }

	void SetUniforms(Shader & shader);

	glm::vec3& GetPoisition() ;
	glm::vec3& GetAmbientColor();

	unsigned int GetId() { return m_LightID; }
public:
	glm::vec3 m_AmbientColor;
	glm::vec3 m_Position;

	float m_Intensivity = 10.0f;

	LightMode m_Mode;

	float m_Radius;

private:
	unsigned int m_LightID;
};



#endif