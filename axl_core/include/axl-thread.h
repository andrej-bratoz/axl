#pragma once
//
#include "axl-macro.h"
#include "axl-defer.h"
#include "axl-exception.h"


#include <thread>
#include <functional>
#include <chrono>

namespace axl {

	template <class T>
	struct future {
	private:
		T result;
		bool _has_result;
		std::function<T()> fnc;
	public:
		T get() {
			if (!_has_result) {
				throw axl::exception("Future has not yet run", -1);
			}
			return result;
		}

		void set_runtime(std::function<T()> f) {
			fnc = f;
		}

		std::function<T()> get_runtime()  {
			return fnc;
		}

		bool has_result() { return _has_result; }

		void set_result(T r) {
			result = r;
			_has_result = true;
		}
	};

	struct simple_thread {
	private:
		std::function<void()> no_arg_func;
		std::thread _tr;
	public:
		void set(std::function<void()> func);
		void start();
		void join();
		void abort();
		bool is_alive();

		static void sleep(int milliseconds);
		static void yield();

		template <typename T>
		static T await(future<T>* fut) {
			simple_thread t;
			t.set([fut]() {
				T result = fut->get_runtime()();
				fut->set_result(result);
			});
			t.start();
			t.join();
			return fut->get();
		}

		template <typename T>
		static void fire_and_forget(future<T>* fut) {
			simple_thread *t = new simple_thread();
			t->set([fut, t]() {
				T result = fut->get_runtime()();
				fut->set_result(result);
				delete t;
				});
			t->start();
		}
	};
};