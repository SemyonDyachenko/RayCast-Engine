#include "glRendererAPI.h"

void glRendererAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void glRendererAPI::SetViewport(float x, float y, float width, float height)
{
	glViewport(x, y, width, height);
}

void glRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glRendererAPI::SetClearColor(glm::vec3 color)
{
	glClearColor(color.x, color.z, color.y,1.0f);
}

void glRendererAPI::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}
