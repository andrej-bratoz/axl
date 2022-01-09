#include <coroutine>
#include <experimental/coroutine>

std::experimental::generator<uint64_t> next_number() {
	static uint64_t current_value = 1;
	while (true) {
		co_yield current_value;
		current_value++;
	}
}