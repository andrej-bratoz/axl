#pragma once

#include "../axl_core/include/axl-logging.h"
#include "../axl_core/include/axl-defer.h"
#include <iostream>

namespace axl::plugin::logging {
	struct logger {
		void start_processing() {
			_allow_enqueue = true;
			if (!_thread_initialized) {
				_thread_initialized = true;
				_processing_thread = std::thread([this]() {
					while (!_messages.empty()) {
						axl::log_message* message = _messages.front();
						defer_lambda([message] () {
							delete message->message;
							delete message->date_time;
							delete message;
						});
						_messages.pop();
						if (message->print_to_stdout || true) {
							std::cout << message->as_string();
						}
					}
				});
			}
		}

		void stop_processing() {
			_allow_enqueue = false;
			_processing_thread.join();
		}

		void enqueue(axl::log_message* msg) {
			if (!_allow_enqueue) return;
			_messages.emplace(msg);
		}

	private:
		bool _thread_initialized;
		bool _allow_enqueue;
		std::queue<axl::log_message*> _messages;
		std::thread _processing_thread;
	};
}