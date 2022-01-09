#pragma once

#include <string>
#include <cstdint>

namespace axl {
	struct exception {
	private:
		std::string _message;
		int32_t _error_code;
	public:
		exception(const std::string& message, int32_t err_code) {
			_message = message;
			_error_code = err_code;
		}

		std::string message() {
			return _message;
		}

		int32_t error_code() {
			return _error_code;
		}
	};
};