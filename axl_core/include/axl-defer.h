#pragma once
#include "axl-macro.h"
#include <functional>

namespace axl {
	namespace pvt {
		template <class TR>
		struct _defer_struct_0 {
			typedef std::function< TR() > func_type;
			explicit _defer_struct_0(func_type _func) : func(_func) {}
			~_defer_struct_0() { func(); }
		private:
			func_type func;
		};

		template <class TR>
		struct _defer_struct_safe_0 {
			typedef std::function< TR() > func_type;
			explicit _defer_struct_safe_0(func_type _func) : func(_func) {}
			~_defer_struct_safe_0() { try { func(); } catch (...) {}}
		private:
			func_type func;
		};
	}

#define defer_lambda(x) axl::pvt::_defer_struct_0<void> CONCAT(CONCAT(__defer_struct_0__, __LINE__),__LINE__) (x);
#define defer(x,...) axl::pvt::_defer_struct_0<void> CONCAT(CONCAT(__defer_struct_0__, __LINE__),__LINE__) ([]() {x __VA_ARGS__ });
#define defer_nox(x,...) axl::pvt::_defer_struct_safe_0<void> CONCAT(CONCAT(__defer_struct_0__, __LINE__), __LINE__)([]() {try{ x __VA_ARGS__} catch(...) {} });
};