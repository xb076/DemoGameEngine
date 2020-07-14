#pragma once


#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error This application only supports windows!
#endif

#ifdef ENGINE_DEBUG
	#if defined(ENGINE_PLATFORM_WINDOWS)
		#define ENGINE_DEBUGBREAK() __debugbreak()
	#elif defined(ENGINE_PLATFORM_LINUX)
		#include <signal.h>
		#define ENGINE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define ENGINE_ENABLE_ASSERTS
	#else
		#define ENGINE_DEBUGBREAK()
#endif


#ifdef ENGINE_ENABLE_ASSERTS
#define ENGINE_ASSERT(x, ...) { if(!(x)) { LOG_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); ENGINE_DEBUGBREAK(); } }
#define ENGINE_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); ENGINE_DEBUGBREAK(); } }
#else
#define ENGINE_ASSERT(x, ...)
#define ENGINE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)


#define ENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


