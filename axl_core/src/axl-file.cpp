#include "..\include\axl-file.h"
#include "..\include\axl-defer.h"


std::vector<std::string> axl::read_text_file_all_lines(const std::string& path) {
	std::ifstream its;
	its.open(path);
	defer_lambda([&its]() {its.close(); });
	std::string result((std::istreambuf_iterator<char>(its)), std::istreambuf_iterator<char>());
	return split(result, "\n");
}

std::string axl::read_text_file_all(const std::string& path) {
	std::ifstream its;
	its.open(path);
	defer_lambda([&its]() {its.close(); });
	std::string result((std::istreambuf_iterator<char>(its)), std::istreambuf_iterator<char>());
	return result;
}

std::vector<std::string> axl::split(const std::string& s, const std::string& seperator)
{
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;
	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
	return output;
}

void axl::file_write(const std::string& string, const std::string& file)
{
	std::ofstream _ofstream;
	_ofstream.open(file.c_str());
	defer_lambda([&_ofstream]() { _ofstream.close(); })
	_ofstream << string;		
}

