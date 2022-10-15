#include "maolib_logger.h"
#include "../maolib_time/maolib_time.h"
#include<fstream>
#ifdef WIN32
#include<filesystem>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

using namespace maolib::logger;
int64_t maolib::logger::interval;
maolib::logger::_log_level maolib::logger::min_level;
uint64_t maolib::logger::next_idx;
list<maolib::logger::_log> maolib::logger::log_cache;
bool maolib::logger::is_disposing;
std::mutex maolib::logger::mutex;
thread* maolib::logger::thd_p;
char maolib::logger::log_msg_buff[65536] = "";

const char* maolib::logger::_log_level_str[] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
};

const char* maolib::logger::_log_level_str_ANSI[] = {
#ifdef WIN32
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
#else
	"\e[1;32mDEBUG\e[0;37m",
	"INFO\e[0;37m",
	"\e[1;33mWARN\e[0;37m",
	"\e[0;91mERROR\e[0;37m",
	"\e[1;31mFATAL\e[0;37m"
#endif
};



void maolib::logger::init()
{
	interval = 100;
	next_idx = 10000000;
	is_disposing = false;
	min_level = LOG_LEVEL_DEBUG;
	thd_p = new thread(log_thread);
}

void maolib::logger::dispose()
{
	is_disposing = true;
	thd_p->join();
	cout << "logger stop." << endl;
}

void maolib::logger::log(_log_level level, string format, ...)
{
	if (min_level < level)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	switch (level) {
	case LOG_LEVEL_DEBUG:
		debug(msg);
		break;
	case LOG_LEVEL_INFO:
		info(msg);
		break;
	case LOG_LEVEL_WARN:
		warn(msg);
		break;
	case LOG_LEVEL_ERROR:
		error(msg);
		break;
	case LOG_LEVEL_FATAL:
		fatal(msg);
		break;
	default:
		break;
	}
}

void maolib::logger::debug(string format, ...)
{
	if (min_level > LOG_LEVEL_DEBUG)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	mutex.lock();
	time_t result = std::time(nullptr);
	_log log = { get_idx(),result,LOG_LEVEL_DEBUG,msg };
	log_cache.push_back(log);
	mutex.unlock();
}

void maolib::logger::info(string format, ...)
{
	if (min_level > LOG_LEVEL_INFO)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	mutex.lock();
	time_t result = std::time(nullptr);
	_log log = { get_idx(),result,LOG_LEVEL_INFO,msg };
	log_cache.push_back(log);
	mutex.unlock();
}

void maolib::logger::warn(string format, ...)
{
	if (min_level > LOG_LEVEL_WARN)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	mutex.lock();
	time_t result = std::time(nullptr);
	_log log = { get_idx(),result,LOG_LEVEL_WARN,msg };
	log_cache.push_back(log);
	mutex.unlock();
}

void maolib::logger::error(string format, ...)
{
	if (min_level > LOG_LEVEL_ERROR)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	mutex.lock();
	time_t result = std::time(nullptr);
	_log log = { get_idx(),result,LOG_LEVEL_ERROR,msg };
	log_cache.push_back(log);
	mutex.unlock();
}

void maolib::logger::fatal(string format, ...)
{
	if (min_level > LOG_LEVEL_FATAL)return;
	string msg;
	va_list args;
	va_start(args, format);
	int len = vsprintf(log_msg_buff, format.c_str(), args);
	msg = string(log_msg_buff, len);
	va_end(args);
	mutex.lock();
	time_t result = std::time(nullptr);
	_log log = { get_idx(),result,LOG_LEVEL_FATAL,msg };
	log_cache.push_back(log);
	mutex.unlock();
}

uint64_t maolib::logger::get_idx()
{
	if (next_idx > 99999999)next_idx = 10000000;
	return next_idx++;
}

void maolib::logger::log_thread()
{
	
	cout << "logger start." << endl;
	list<_log> logs;
	while (!is_disposing || log_cache.size() != 0) {
		mutex.lock();
		move(log_cache.begin(), log_cache.end(), back_inserter(logs));
		log_cache.clear();
		mutex.unlock();
		for (_log log : logs) {
			string root = ".";
#ifdef WIN32

			root = filesystem::current_path().generic_string();
			string stdout_str = "";
#else
			string stdout_str = "\e[0;37m";
#endif
			stdout_str += "[" + to_string(log.idx) + "]" + "[" + time::get_now_string() + "]" + "[" + _log_level_str_ANSI[log.level] + "] " + log.msg;
			cout << stdout_str << endl;
			string path = root + "/logs/" + time::get_now_string("%Y%m%d");
#ifdef WIN32
			std::filesystem::create_directories(path);
#else
			string syscmd="mkdir -p "+path;
			system(syscmd.c_str());
#endif

			string filename = path + "/log_" + time::get_now_string("%Y%m%d%H");
			fstream log_file;
			log_file.open(filename, ios_base::app);
			if (log_file.is_open()) {
				log_file << stdout_str << endl;
				log_file.close();
			}
			else {
				cout << "log file " << filename << " open failed." << endl;
			}
		}
		logs.clear();
		this_thread::sleep_for(std::chrono::milliseconds(interval));
	}
}