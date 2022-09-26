// maolib_time.h : Header file for your target.

#pragma once
#include <string>

namespace maolib {
	namespace time {
		/// <summary>
		/// get milliseconds since epoch to now
		/// </summary>
		/// <returns>milliseconds</returns>
		extern uint64_t get_now_timestamp();
		/// <summary>
		/// get now date and time according to format string format
		/// </summary>
		/// <param name="format">format string ($f=milliseconds)</param>
		/// <returns>the date and time string</returns>
		extern std::string get_now_string(std::string format="%Y-%m-%d %H:%M:%S.$f");
	}
}
