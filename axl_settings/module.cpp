#include "../axl_core/include/axl-module.h"
#include "../axl_core/include/axl-message-bus.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

axl::message_bus* g_message_bus;
axl::message_bus_subscriber* g_subscriber;

struct module_subscriber : public axl::message_bus_subscriber {
	virtual axl::message_bus_token getToken() const {
		return 12345;
	}
	void handle_message(axl::message_bus_notification notification) {
		m_mtx.lock();
		std::cout << "MESSAGE_BUS" << ": " << notification.arg1 << std::endl;
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(100ms);
		m_mtx.unlock();
	}
private:
	std::mutex m_mtx;
};

void message_pump() {
	g_subscriber = new module_subscriber();
	g_message_bus->add_subscription(g_subscriber);
}
 
extern "C" {
	void AXL_MODULE_LOAD(void* message_bus) {
		g_message_bus = static_cast<axl::message_bus*>(message_bus);
		message_pump();
	}

	void AXL_MODULE_UNLOAD() {
		g_subscriber->unsubscribe(g_message_bus,12345);
		delete g_subscriber;
	}
}
