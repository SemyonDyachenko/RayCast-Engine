#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <glm.hpp>

#include "Shader.h"
#include "Texture.h"

namespace RayCast {

	class RAYCAST_API Material
	{
	public:
		Material();
		Material(Texture* diffuseTexture, Texture* specularTexture, float shininess, glm::vec3 color);
		virtual ~Material();

		Texture& GetDiffuseTexture();
		Texture& GetSpecularTexture();

		void AddDiffuseTexture(Texture* diffuse);
		void AddSpecularTexture(Texture* specular);

		bool& IsActive();
		bool& IsVisisble();

		void Enable();
		void Disable();

		void Textured() { m_Textured = true; }
		bool& IsTextured() { return m_Textured; }

		float& GetShininess();

		glm::vec3& GetColor();

		void SetUniforms(Shader& shader);

	private:
		glm::vec3 m_Color;
		float m_Shininess;
		Texture* m_iDiffuseTexture;
		Texture* m_iSpecularTexture;

		bool m_Active = false;
		bool m_Visibility = true;
		bool m_Textured = false;

	};

}


#endif