#ifndef RENDERER_H
#define RENDERER_H


#include "Shader.h"
#include "Mesh.h"
#include "../Camera/Camera.h"
#include "Cubemap.h"
#include "../Core/Core.h"


namespace RayCast {

	class RAYCAST_API Renderer
	{
	public:
		virtual ~Renderer() = default;

		static void Init();

		static void SetViewport(glm::vec4 viewport);

		static void SetClearColor(glm::vec3 color);

		static void SubmitCamera(Shader* shader, Camera* camera);

		static void Render(Shader* shader, Mesh* mesh, glm::mat4 transformation);

	};

}

#endif