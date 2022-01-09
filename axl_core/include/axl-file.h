#pragma once

#include "axl-macro.h"
#include "axl-defer.h"
#include <string>
#include <fstream>
#include <vector>

namespace axl {

	void file_write(const std::string& string, const std::string& file);
	std::vector<std::string> split(const std::string& s, const std::string& seperator);
	std::string read_text_file_all(const std::string& path);
	std::vector<std::string> read_text_file_all_lines(const std::string& path);

	template <typename t>
	void file_write_binary(const std::vector<t>& data, const std::string& path) {
		std::ofstream ofs;
		ofs.open(path, std::ios::binary);
		defer_lambda([&ofs]() {ofs.close(); });

		for (t item : data) {
			ofs.write(reinterpret_cast<const char*>(&item), sizeof(t));
		}
	}

	template <typename t>
	void file_append_binary(const std::vector<t>& data, std::string path) {
		std::ofstream ofs;
		ofs.open(path, std::ios::binary | std::ios_base::app);
		defer_lambda([&ofs]() {ofs.close(); });

		for (t item : data) {
			ofs.write(reinterpret_cast<const char*>(&item), sizeof(t));
		}
	}

	struct text_file {
		private:
			std::ofstream _ofs;
		public:
			void open(std::string path, bool append) {
				if (append) {
					_ofs.open(path, std::ios_base::app);
				}
				else {
					_ofs.open(path);
				}
			}
			void write(const std::string& str) {
				_ofs << str;
			}

			void writeln(const std::string& str) {
				_ofs << str << std::endl;
			}
	};

	struct binary_file {
		private:
			std::ofstream _ofs;

		public:
			void open(std::string path, bool append) {
				if (append) {
					_ofs.open(path, std::ios::binary | std::ios_base::app);
				} else {
					_ofs.open(path, std::ios::binary);
				}
			}
			template <typename t>
			void write(t data) {
				_ofs.write(reinterpret_cast<const char*>(&data), sizeof(t));
			}

			template <>
			void write<std::string>(std::string str) {
				_ofs << str;
			}

			template <>
			void write<const char*>(const char* str) {
				_ofs << str;
			}

			~binary_file() {
				_ofs.close();
			}
	};
}