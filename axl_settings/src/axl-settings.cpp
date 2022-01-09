#include "axl-settings.h"

axl::plugin::settings::settings_proxy* g_settings_proxy;

axl::plugin::settings::settings_proxy* get_settings_proxy_object()
{
	if (g_settings_proxy == nullptr) {
		g_settings_proxy = new axl::plugin::settings::settings_proxy();
	}
	return g_settings_proxy;
}



void open_settings() {
	int o = 0;

}