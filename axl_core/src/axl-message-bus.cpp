
#include "../include/axl-macro.h"
#include "../include/axl-message-bus.h"

axl::message_bus_token axl::message_bus_subscriber::subscribe(axl::message_bus& bus)
{
	return bus.add_subscription(this);
}

void axl::message_bus_subscriber::unsubscribe(axl::message_bus* bus, axl::message_bus_token token) {
	bus->remove_subscription(token);
}

axl::message_bus_token axl::message_bus::add_subscription(axl::message_bus_subscriber* subscriber) {
	this->m_subscribers.push_back(subscriber);
	return 0;
}

void axl::message_bus::remove_subscription(axl::message_bus_token token) {
	auto it = std::find_if(this->m_subscribers.begin(), this->m_subscribers.end(), [&token](const message_bus_subscriber* e) {
		return e->getToken() == token;
	});
	this->m_subscribers.erase(it);
}

void axl::message_bus::queue_notification(axl::message_bus_notification notification) {
	for (axl::message_bus_subscriber* data : this->m_subscribers) {
		auto token = data->getToken();
		if (token == notification.destination) {
			data->handle_message(notification);
			return;
		}
	}
}

void axl::message_bus::queue_notification_async(axl::message_bus_notification notification) {

	std::thread([notification,this]() {
		for (axl::message_bus_subscriber* data : this->m_subscribers) {
			auto token = data->getToken();
			if (token == notification.destination) {
				data->handle_message(notification);
				return;
			}
		}
	}).detach();
}