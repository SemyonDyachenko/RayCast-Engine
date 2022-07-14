#ifndef RENDERER_H
#define RENDERER_H


#include "Shader.h"
#include "Mesh.h"
#include "../Camera/Camera.h"
#include "Cubemap.h"


#include "RendererAPI.h"

class Renderer
{
public:
	virtual ~Renderer() = default;	

	static void Init();

	static void SetViewport(glm::vec4 viewport);

	static void SetClearColor(glm::vec3 color);

	static void Clear();

	static void SubmitCamera(Shader * shader, EditorCamera* camera);

	static void Render(Shader * shader,Mesh * mesh,glm::mat4 transformation);

	static void RenderTexturedQuad(EditorCamera* camera);
	static void RenderCube(EditorCamera* camera) {}

private:
	static std::shared_ptr<RendererAPI> m_Renderer;
};

#endif