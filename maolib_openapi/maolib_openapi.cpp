#include "maolib_openapi.h"
#include "../maolib_logger/maolib_logger.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
namespace maolib
{
	namespace OpenApiClient
	{

		OpenApiClient::OpenApiClient():pRecvThread(nullptr),_socket(-1),isConnected(false)
		{
		}
		OpenApiClient::~OpenApiClient()
		{
			if(isConnected){
				close(_socket);
			}

			isConnected=false;
		}
		bool OpenApiClient::Connect(string host)
		{
			if(isConnected){
				close(_socket);
			}

			isConnected=false;
			_socket = socket(AF_INET, SOCK_STREAM, 0);

			if (_socket == -1)
			{
				logger::error("Could not create socket");
				return false;
			}

			struct sockaddr_in server;

			struct hostent *he;
			struct in_addr **addr_list;

			if ((he = gethostbyname(host.c_str())) == NULL)
			{
				logger::error("gethostbyname");
				return false;
			}

			addr_list = (struct in_addr **)he->h_addr_list;
			char ip[17];
			for (int i = 0; addr_list[i] != NULL; i++)
			{
				strcpy(ip, inet_ntoa(*addr_list[i]));
				break;
				;
			}

			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_family = AF_INET;
			server.sin_port = htons(80);

			if (connect(_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
			{
				logger::error("connect error");
				return false;
			}

			logger::info("Connected");
			isConnected = true;
			return true;
		}
		Json OpenApiClient::Request(REQUEST_METHOD method, string endpoint, Json *payload)
		{
			return Json();
		}
		void Request(REQUEST_METHOD method, string endpoint, Json *payload = nullptr, void (*callback)(Json) = nullptr)
		{
		}
		void OpenApiClient::Dispose() {
			if(isConnected){
				close(_socket);
			}
			isConnected=false;
		}
	}
}