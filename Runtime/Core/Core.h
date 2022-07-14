#pragma once

#include <iostream>
#include <memory>




#ifdef _WIN32
#define RAYCAST_WINDOWS_PLATFORM

	#ifdef RAYCAST_WINDOWS_PLATFORM
		#define RAYCAST_API __declspec(dllexport)
	#endif

#elif defined(__APPLE__) || defined(__MACH__)
#error "Apple Macintosh is not supported!"

#elif defined(__IOS__)
#error "IOS simulation not supported"

#elif defined(__ANDROID__)
#define FATON_ANDROID_PLATFORM
#error "Android is not currently supported"

#elif defined(__linux__)
#define FATON_LINUX_PLATFORM
#error "Linux is not currently supported"

#else
#error "Unknow platform is not supported"

#endif

#ifdef _OPENGL
#define ENGINE_OPENGL_API

#elif defined(_VULKAN)
#error "Vulkan API is not supported!"

#elif defined(_DIRECTX)
#error "Microsoft DirectX is not supported!"

#endif

