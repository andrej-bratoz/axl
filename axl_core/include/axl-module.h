#pragma once

#include "../include/axl-macro.h"
#include "../include/axl-message-bus.h"

struct axl_module {
	virtual void module_load(axl::message_bus& msgbus) = 0;
	virtual void module_unload() = 0;
};
