#pragma once

#include "Core.h"

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace RayCast {

	class RAYCAST_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }



	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define ENGINE_ERROR(...) RayCast::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_WARNING(...) RayCast::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_INFO(...) RayCast::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_TRACE(...) RayCast::Log::GetCoreLogger()->trace(__VA_ARGS__)