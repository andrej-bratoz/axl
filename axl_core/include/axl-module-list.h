#pragma once
#include <cstdint>
#include <vector>
#include <string>


namespace axl {
	struct module_list_entry {
		std::string name;
		
	};

	struct module_list {
		module_list(std::string);
		std::vector<module_list_entry>::const_iterator begin();
	private:
		std::vector<module_list_entry> _entry;
		std::string file_name;
		
	};
}