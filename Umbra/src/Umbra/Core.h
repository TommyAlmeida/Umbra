#pragma once
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