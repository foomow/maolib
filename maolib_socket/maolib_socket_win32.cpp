#ifdef WIN32
#define _HAS_STD_BYTE 0
#include "maolib_socket.h"
#include "../maolib_logger/maolib_logger.h"
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


namespace maolib
{
	namespace client_socket
	{
		int connect(string host, int port)
		{
			WSADATA wsaData;
			int iResult;

			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				printf("WSAStartup failed: %d\n", iResult);
				return -1;
			}

			struct addrinfo* result = NULL,
				* ptr = NULL,
				hints;

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			iResult = getaddrinfo(host.c_str(), to_string(port).c_str(), &hints, &result);
			if (iResult != 0) {
				printf("getaddrinfo failed: %d\n", iResult);
				WSACleanup();
				return -1;
			}

			ptr = result;
			printf("connecting to %s:%d\n", inet_ntoa(((struct sockaddr_in*)ptr->ai_addr)->sin_addr), ntohs(((sockaddr_in*)(ptr->ai_addr))->sin_port));

			SOCKET ConnectSocket = INVALID_SOCKET;

			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);

			if (ConnectSocket == INVALID_SOCKET) {
				printf("Error at socket(): %ld\n", WSAGetLastError());
				freeaddrinfo(result);
				WSACleanup();
				return 1;
			}

			iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

			if (ConnectSocket == INVALID_SOCKET) {
				printf("Error at socket(): %ld\n", WSAGetLastError());
				freeaddrinfo(result);
				WSACleanup();
				return -1;
			}
			return ConnectSocket;
		}
		int send(int socket_fd, string requestPayload)
		{
			int iResult = ::send(socket_fd, requestPayload.c_str(), (int)strlen(requestPayload.c_str()), 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(socket_fd);
				WSACleanup();
				return -1;
			}
			return iResult;
		}
		int recv(int socket_fd, void* buff, size_t len, int flag)
		{
			return ::recv(socket_fd, (char*)buff, len, flag);
		}
		int close_socket(int socket_fd)
		{
			return ::closesocket(socket_fd);
		}
	}
}
#endif