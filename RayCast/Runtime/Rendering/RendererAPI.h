#pragma once


#include <glm.hpp>
#include <memory>


class RendererAPI
{
public:
	virtual ~RendererAPI() = default;
	
	virtual void SetViewport(float x, float y, float width, float height) = 0;

	virtual void Init() = 0;
	// clear color and buffer bit
	virtual void Clear() = 0;
	
	virtual void SetClearColor(glm::vec3 color) = 0;

	virtual void SetClearColor(float r, float g, float b) = 0;

	static std::shared_ptr<RendererAPI> Create();
};

