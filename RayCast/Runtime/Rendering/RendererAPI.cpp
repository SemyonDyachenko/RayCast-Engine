#include "RendererAPI.h"


#include "../Platform/OpenGL/glRendererAPI.h"

std::shared_ptr<RendererAPI> RendererAPI::Create()
{
	return std::make_shared<glRendererAPI>();
}
