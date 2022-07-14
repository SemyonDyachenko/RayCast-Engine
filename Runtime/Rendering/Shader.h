#ifndef SHADER_H
#define SHADER_H

#include "../Core/Core.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace RayCast {

	class RAYCAST_API Shader {
	public:
		unsigned int ID;

		Shader(const char* vertex_path, const char* fragment_path);

		virtual ~Shader();

		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);
		void SetMat4(const std::string& name, glm::mat4 value);
		void SetVec3(const std::string& name, glm::vec3 value);
		void SetVec4(const std::string& name, glm::vec4 value);

		void use();
		void unuse();
	};

}

#endif