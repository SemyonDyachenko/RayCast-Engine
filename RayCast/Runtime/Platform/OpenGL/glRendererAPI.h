#ifndef GL_RENDERER_API
#define GL_RENDERER_API

#include <GL/glew.h>
#include "../../Rendering/RendererAPI.h"

class glRendererAPI : public RendererAPI
{
public:
	glRendererAPI() = default;

	void Init() override;

	void SetViewport(float x, float y, float width, float height) override;
	void Clear() override;
	void SetClearColor(glm::vec3 color) override;
	void SetClearColor(float r, float g, float b) override;
};

#endif