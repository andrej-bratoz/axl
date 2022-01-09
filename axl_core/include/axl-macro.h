#pragma once
#ifdef WIN32
#include <Windows.h>
#endif // WIN32
#include <thread>


#define CONCAT_INTERNAL(a, b) a ## b
#define CONCAT(a, b) CONCAT_INTERNAL(a, b)
#define NOX(x) {try {x} catch (...){}}

#define VALUE_PROPERTY(T, name)							\
	private: T _##name;									\
	public: void set##name(T value){ _##name = value;}	\
			T    get##name() {return _##name;}			\

#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif // WIN32

typedef void(__stdcall* AXL_MODULE_ENTRY)(void*);
typedef void(__stdcall* AXL_MODULE_UNLOAD_ENTRY)();

#define AXL_MODULE_LOAD __declspec(dllexport) __stdcall axl_module_load
#define AXL_MODULE_LOAD_NAME "axl_module_load"

#define AXL_MODULE_UNLOAD __declspec(dllexport) __stdcall axl_module_unload
#define AXL_MODULE_UNLOAD_NAME "axl_module_unload"


namespace axl
{
	inline int load_module(const char* module_name, void* arg) {
		HINSTANCE hModule = LoadLibrary(module_name);
		if (!hModule) return -1;

		AXL_MODULE_ENTRY entry = (AXL_MODULE_ENTRY)GetProcAddress(hModule, AXL_MODULE_LOAD_NAME);
		if (!entry) return -1;

		entry(arg);
		return 0;
	}

	inline int unload_module(const char* module_name) {
		HINSTANCE hModule = LoadLibrary(module_name);
		if (!hModule) return -1;
		AXL_MODULE_UNLOAD_ENTRY entry = (AXL_MODULE_UNLOAD_ENTRY)GetProcAddress(hModule, AXL_MODULE_UNLOAD_NAME);
		if (!entry) return -1;
		entry();
		return 0;
	}
}

//
