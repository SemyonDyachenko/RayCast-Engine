#include "Window.h"

#ifdef _WIN32
#include "../Platform/Windows/glWindow.h"
#endif	

std::unique_ptr<Window> Window::Create(WindowProps& props)
{
	return std::make_unique<glWindow>(props);
}
