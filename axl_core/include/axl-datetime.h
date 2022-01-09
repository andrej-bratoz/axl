#pragma once
#include <cstdint>

namespace axl {
	struct date_time {
		
		date_time() {

		}

		date_time(const date_time& t) :
			year(t.year), month(t.month),
			day(t.day), hour(t.hour),
			minute(t.minute), second(t.second),
			millisecond(t.millisecond)
		{}

		date_time(date_time&& t) :
			year(t.year), month(t.month),
			day(t.day), hour(t.hour),
			minute(t.minute), second(t.second),
			millisecond(t.millisecond)
		{}
		size_t year;
		size_t month;
		size_t day;
		size_t hour;
		size_t minute;
		size_t second;
		size_t millisecond;

		static date_time&& now() {
			date_time dt;
			return std::move(dt);
		}
	};
}