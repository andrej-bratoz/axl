#pragma once 

#include "axl-macro.h"
#include <cstdint>
#include <vector>
#include <variant>

namespace axl {
	struct message_bus;
	typedef uint64_t message_bus_token;

	struct message_bus_notification {

		message_bus_token source;
		message_bus_token destination;

		uint64_t message;
		uint64_t arg1;
		int64_t arg2;
		void* ptr;

		bool accepted;
		bool consumer_destroy;
	};

	struct message_bus_subscriber {
		message_bus_token subscribe(axl::message_bus& bus);
		void unsubscribe(axl::message_bus* bus, axl::message_bus_token token);
		virtual message_bus_token getToken() const = 0;
		virtual void handle_message(message_bus_notification notification) {}
	};
	

	struct message_bus {
		message_bus_token add_subscription(message_bus_subscriber* subscriber);
		void remove_subscription(message_bus_token token);
		void queue_notification(message_bus_notification notification);
		void queue_notification_async(message_bus_notification notification);

	private:
		std::vector<message_bus_subscriber* > m_subscribers;
	};
}