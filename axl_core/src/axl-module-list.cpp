#include "../include/axl-module-list.h"

std::vector<axl::module_list_entry>::const_iterator axl::module_list::begin()
{
	return this->_entry.begin();
}