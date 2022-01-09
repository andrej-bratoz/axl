#pragma once
#include "axl-datetime.h"

#include <queue>
#include <thread>
#include <string>
#include <sstream>

namespace axl {
	enum class log_message_severity {
		debug,
		info,
		warning,
		error, 
		critical
	};

	struct log_message {
		log_message_severity severity;
		char* category;
		char* message;
		axl::date_time* date_time;
		bool print_to_stdout;

		virtual std::string as_string() {
			std::stringstream ss;
			ss << "[" << category << "]\t" << message << std::endl;
			return ss.str();
		}
	};
};