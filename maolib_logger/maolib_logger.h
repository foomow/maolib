#pragma once
#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <ctime>
#include <mutex>
#include <thread>
#include <cstring>
#include <cstdarg>
using namespace std;
namespace maolib {
	namespace logger {
		enum _log_level {
			LOG_LEVEL_DEBUG,
			LOG_LEVEL_INFO,
			LOG_LEVEL_WARN,
			LOG_LEVEL_ERROR,
			LOG_LEVEL_FATAL
		};

		struct _log {
			uint64_t idx;
			time_t time;
			_log_level level;
			string msg;
		};
		extern char log_msg_buff[];
		extern const char* _log_level_str[];
		extern const char* _log_level_str_ANSI[];

		extern void init();
		extern void dispose();
		extern void log(_log_level level, string format, ...);
		extern void debug(string format, ...);
		extern void info(string format, ...);
		extern void warn(string format, ...);
		extern void error(string format, ...);
		extern void fatal(string format, ...);

		extern int64_t interval;
		extern _log_level min_level;
		extern uint64_t next_idx;
		extern list<_log> log_cache;
		extern bool is_disposing;
		extern std::mutex mutex;
		extern thread* thd_p;
		extern uint64_t get_idx();
		extern void log_thread();
	}
}