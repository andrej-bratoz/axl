#include "../include/axl-helpers.h"
#include "../include/axl-logging.h"
#include "../include/axl-message-bus.h"
#include "../include/axl-datetime.h"

extern axl::message_bus* g_message_bus;


void axl::helpers::log_start() {
	axl::message_bus_notification ntf1;
	ntf1.message = 0x1;
	ntf1.destination = 0x2;
	g_message_bus->queue_notification(ntf1);
}

void axl::helpers::log_end() {
	axl::message_bus_notification ntf2;
	ntf2.message = 0x2;
	ntf2.destination = 0x2;
	g_message_bus->queue_notification(ntf2);
}


void axl::helpers::log(std::string category, std::string message) {
	axl::message_bus_notification ntf;

	axl::log_message* msg = new axl::log_message();
	msg->category = axl::helpers::AllocString(category);
	msg->date_time = axl::helpers::AllocDateTimeNow();
	msg->message = axl::helpers::AllocString(message);
	msg->severity = axl::log_message_severity::info;

	ntf.destination = 0x2;
	ntf.message = 0x0003L;
	ntf.ptr = msg;
	ntf.consumer_destroy = true;

	g_message_bus->queue_notification(ntf);


}