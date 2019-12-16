#pragma once

#include <memory>

#ifdef UB_PLATFORM_WINDOWS
#ifdef UB_BUILD_DLL
#define UMBRA_API __declspec(dllexport)
#else
#define UMBRA_API __declspec(dllimport)
#endif
#else
#error Umbra only supports Windows!
#endif

#define BIT(x) (1 << x)

namespace Umbra {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}