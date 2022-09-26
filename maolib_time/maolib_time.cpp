// maolib_time.cpp : Source file for your target.
//

#include "maolib_time.h"
#include <chrono>
#include <iostream>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace maolib {
	namespace time {
		uint64_t get_now_timestamp() {
			return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		}
		std::string get_now_string(std::string format) {

			time_t rawtime;
			struct tm* timeinfo;
			char buffer[80];

			std::time(&rawtime);
			int f = (int)(get_now_timestamp() % 1000);
			timeinfo = localtime(&rawtime);

			int len = strftime(buffer, 80, format.c_str(), timeinfo);

			std::string ret = std::string(buffer, len);
			int f_pos = ret.find("$f");
			if (f_pos >= 0) {
				char f_str[4];
				sprintf(f_str, "%03d", f);
				ret.replace(f_pos, 2, f_str);
			}
			return ret;
		}
	}
} 