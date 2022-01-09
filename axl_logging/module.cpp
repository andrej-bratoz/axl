#include "../axl_core/include/axl-module.h"
#include "../axl_core/include/axl-message-bus.h"
//
#include "src/axl-log.h"
#include <mutex>

axl::message_bus* g_message_bus;
axl::message_bus_subscriber* g_subscriber;

#define AXM_LOGGING 0x2
//
#define AXM_LOGGING_START 0x0001L
#define AXM_LOGGING_STOP 0x0002L
#define AXM_LOGGING_ENQUEUE 0x0003L


struct module_subscriber : public axl::message_bus_subscriber {
	virtual axl::message_bus_token getToken() const {
		return AXM_LOGGING;
	}
	void handle_message(axl::message_bus_notification notification) {
		m_mtx.lock();
			
		switch (notification.message)
		{
		case AXM_LOGGING_START:
			logger.start_processing();
			break;
		case AXM_LOGGING_STOP:
			logger.stop_processing();
			break;
		case AXM_LOGGING_ENQUEUE:
			enqueue_message(notification);
			break;
		default:
			break;
		}
		m_mtx.unlock();
	}
private:
	void enqueue_message(const axl::message_bus_notification& notification) {
		axl::log_message* msg = (axl::log_message*)notification.ptr;
		logger.enqueue(msg);
	}
	std::mutex m_mtx;
	axl::plugin::logging::logger logger;
};

extern "C" {
	void AXL_MODULE_LOAD(void* message_bus) {
		g_subscriber = new module_subscriber();
		g_message_bus = static_cast<axl::message_bus*>(message_bus);
		g_message_bus->add_subscription(g_subscriber);
	}

	void AXL_MODULE_UNLOAD() {
		g_subscriber->unsubscribe(g_message_bus, AXM_LOGGING);
		delete g_subscriber;
	}
}