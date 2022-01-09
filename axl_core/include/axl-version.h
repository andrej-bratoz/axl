#pragma once
#include <cstdint>
#include <sstream>

namespace axl {
	struct version {
		uint32_t major;
		uint32_t minor;
		uint32_t revision;
		uint32_t build;

		version(uint32_t maj, uint32_t min, uint32_t rev, uint32_t b) : 
			major(maj), minor(min), revision(rev), build(b)
		{}
		version(const version& v) :
			major(v.major), minor(v.minor), revision(v.revision),
			build(v.build)
		{}

		version(version&& v) noexcept:
			major(v.major), minor(v.minor), revision(v.revision),
			build(v.build)
		{}


		bool operator== (const version& v) const;
		bool operator>(const version& v) const;
		bool operator<(const version& v) const;
		bool operator>=(const version& v) const;
		bool operator<=(const version& v) const;
		std::string&& to_string();

		static version&& parse(std::string version);
	};
}