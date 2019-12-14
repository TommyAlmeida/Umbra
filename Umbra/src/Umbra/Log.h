#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Umbra {
	class UMBRA_API Log
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

//Core log macros
#define UB_CORE_ERROR(...) ::Umbra::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UB_CORE_WARN(...) ::Umbra::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UB_CORE_INFO(...) ::Umbra::Log::GetCoreLogger()->info(__VA_ARGS__)
#define UB_CORE_TRACE(...) ::Umbra::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define UB_CORE_FATAL(...) ::Umbra::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define UB_CLIENT_ERROR(...) ::Umbra::Log::GetClientLogger()->error(__VA_ARGS__)
#define UB_CLIENT_WARN(...) ::Umbra::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UB_CLIENT_INFO(...) ::Umbra::Log::GetClientLogger()->info(__VA_ARGS__)
#define UB_CLIENT_TRACE(...) ::Umbra::Log::GetClientLogger()->trace(__VA_ARGS__)
#define UB_CLIENT_FATAL(...) ::Umbra::Log::GetClientLogger()->critical(__VA_ARGS__)