#include "../include/axl-version.h"

std::string&& axl::version::to_string()
{
	std::stringstream ss;
	ss << major << "." << minor << "." << revision << "." << build;
	std::string result(ss.str().c_str());
	return std::move(result);
}

axl::version&& axl::version::parse(std::string version) {
	for (int ch = 0; ch < version.length(); ch++) {

	}
	axl::version v(1,0,0,0);
	return std::move(v);

}

bool axl::version::operator==(const axl::version& v) const {
	return	major == v.major &&
		minor == v.minor &&
		revision == v.revision &&
		build == v.build;
}

bool axl::version::operator>(const axl::version& v) const {
	if (major > v.major) return true;
	else if (major == v.major) {
		if (minor > v.minor) return true;
		else if (minor == v.minor) {
			if (revision > v.revision) return true;
			else if (revision == v.revision) {
				if (build > v.build) return true;
			}
		}
	}
	return false;
}

bool axl::version::operator<(const axl::version& v) const {
	return !((*this > v) || (*this == v));
}

bool axl::version::operator>=(const axl::version& v) const {
	return !(*this < v);
}

bool axl::version::operator<=(const axl::version& v) const {
	return !(*this > v);
}
