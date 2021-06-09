#pragma once

#include <iostream>
#include <memory>


#ifdef _WIN32
#define ENGINE_WINDOWS_PLATFORM

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

#define ENGINE_ERROR_01 std::cout << "ERROR_01: None API, or Engine does not see his, or API is currently not ssupported!" << std::endl  // Engine not use , or does not see API
#define ENGINE_ERROR_02(filename) std::cout << "ERROR_02: Error load data from file " << filename << std::endl
#define ENGINE_ERROR_03 std::cout << "RIGIDBODY ERROR: This rigid body is not a dynamic type.\n It is impossible to attach the value of mass\n" // error 1 for rigid body



#define ENGINE_PRINT(text) std::cout << text << std::endl
