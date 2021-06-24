#pragma once

#include "Core.h"

#include <memory>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }



private:
	
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};


#define ENGINE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_WARNING(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)