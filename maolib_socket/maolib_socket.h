#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "../maolib_json/maolib_json.h"
using namespace std;
using namespace maolib::json;
namespace maolib
{
	namespace client_socket
	{
		/// <summary>
		/// connect to server
		/// </summary>
		/// <returns>socket descriptor</returns>
		int connect(string host, int port=80);
		/// <summary>
		/// send string to server
		/// </summary>
		/// <returns>bytes sent or -1 when error</returns>
		int send(int socket_fd, string);
		/// <summary>
		/// receive string to server
		/// </summary>
		/// <returns>bytes received or -1 when error</returns>
		int recv(int socket_fd, char* buff, size_t len, int flag=0);
		/// <summary>
		/// close socket
		/// </summary>
		/// <returns>0 ok or -1 when error</returns>
		int close_socket(int socket_fd);
	}
}