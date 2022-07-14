#include "Shader.h"
#include "Mesh.h"
#include "../Camera/Camera.h"
#ifndef RENDERER_H
#define RENDERER_H


class Renderer
{
public:
	virtual ~Renderer() = default;	

	static void Init();

	static void SubmitCamera(Shader * shader,Camera* camera);

	static void Render(Shader * shader,Mesh * mesh,glm::mat4 transformation);
};

#endif