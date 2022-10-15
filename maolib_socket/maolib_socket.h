#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "../maolib_json/maolib_json.h"
using namespace std;
using namespace maolib::json;
namespace maolib
{
	namespace socket
	{
		int connect(string host, int port);
		int send(int socket_fd, string);
		int recv(int socket_fd, void* buff, size_t len, int flag=0);
		int close_socket(int socket_fd);
	}
}