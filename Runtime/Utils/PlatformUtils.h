#pragma once

#include <string>

#include "../Core/Core.h"

namespace RayCast {
	
	class RAYCAST_API FileDialogs {
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}