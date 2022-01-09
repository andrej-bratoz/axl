#include "../../axl_core/include/axl-defer.h"
#include "../../axl_core/include/axl-refc.h"

void open_settings();


namespace axl::plugin::settings {
	struct settings_proxy {
		void get_propety(){}
	};

	ref_counted_object<settings_proxy>&& get_settings_proxy_object();
}