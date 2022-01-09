#pragma once
#include "axl-message-bus.h"
#include "axl-datetime.h"


namespace axl {
	namespace helpers {
		inline char* AllocString(std::string str) {
			char* chr = new char[str.length() * sizeof(char) + sizeof(char)];
			strcpy_s(chr, str.length() + sizeof(char), str.c_str());
			chr[str.length() * sizeof(char) + sizeof(char) - 1] = '\0';
			return chr;
		}

		inline axl::date_time* AllocDateTimeNow() {
			axl::date_time dt = axl::date_time::now();
			axl::date_time* retval = new axl::date_time(dt);
			return retval;
		}
	
		void log(std::string category, std::string message);
		void log_start();
		void log_end();
	}
}