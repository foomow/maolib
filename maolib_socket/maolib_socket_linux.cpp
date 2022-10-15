#ifdef __linux__
#include "maolib_socket.h"
#include "../maolib_logger/maolib_logger.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace maolib
{
	namespace client_socket
	{

		int connect(string host, int port)
		{
			int _socket = ::socket(AF_INET, SOCK_STREAM, 0);

			if (_socket == -1) {
				logger::error("Could not create socket");
				return _socket;
			}

			struct sockaddr_in server;

			struct hostent* he;
			struct in_addr** addr_list;

			if ((he = gethostbyname(host.c_str())) == NULL) {
				logger::error("gethostbyname");
				return -1;
			}

			addr_list = (struct in_addr**)he->h_addr_list;
			char ip[17];
			for (int i = 0; addr_list[i] != NULL; i++) {
				strcpy(ip, inet_ntoa(*addr_list[i]));
				break;
				;
			}

			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_family = AF_INET;
			server.sin_port = htons(port);

			if (::connect(_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
				logger::error("connect error");
				return -1;
			}
			return _socket;
		}
		int send(int socket_fd, string requestPayload)
		{
			return ::send(socket_fd, requestPayload.c_str(), strlen(requestPayload.c_str()), 0);
		}
		int recv(int socket_fd, void* buff, size_t len, int flag)
		{
			return ::recv(socket_fd, buff, len, flag);
		}
		int close_socket(int socket_fd)
		{
			::close(socket_fd);
		}
	}
}
#endif