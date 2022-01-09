#include "../../axl_core/include/axl-defer.h"
#include "../../axl_core/include/axl-message-bus.h"
#include "../../axl_core/include/axl-defer.h"
#include "../../axl_core/include/axl-refc.h"
#include "../../axl_core/include/axl-logging.h"
#include "../../axl_core/include/axl-macro.h"
#include "../../axl_core/include/axl-helpers.h"
#include <thread>

axl::message_bus* g_message_bus;
int main(int argc, char** argv) {

	g_message_bus = new axl::message_bus();
	defer_lambda([]() {
		axl::helpers::log_end();
		axl::unload_module("axl_logging.dll");
		delete g_message_bus;
		});
	axl::load_module("axl_logging.dll", g_message_bus);
	axl::helpers::log_start();

	for (int i = 0; i < 10000; i++) {
		axl::helpers::log("[AXL/1.0]", "MSG " + std::to_string(i));
	}
}