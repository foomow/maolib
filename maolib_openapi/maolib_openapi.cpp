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
		const char *METHOD_STR[8] = {
			"POST",
			"PUT",
			"GET",
			"PATCH",
			"DELETE",
			"OPTIONS",
			"HEAD",
			"TRACE"};
		OpenApiClient::OpenApiClient() : pRecvThread(nullptr),
										 _socket(-1),
										 isConnected(false),
										 _port(80),
										 _host("localhost")
		{
		}
		OpenApiClient::~OpenApiClient()
		{
			if (isConnected)
			{
				close(_socket);
			}

			isConnected = false;
		}
		bool OpenApiClient::Connect(string host, int port)
		{
			if (isConnected)
			{
				close(_socket);
			}

			isConnected = false;
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
			server.sin_port = htons(port);

			if (connect(_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
			{
				logger::error("connect error");
				return false;
			}
			_host = host;
			_port = port;
			logger::info("Connected");
			isConnected = true;
			return true;
		}
		Json OpenApiClient::Request(REQUEST_METHOD method, string endpoint, Json *payload)
		{
			requestLock.lock();
			if (!isConnected)
			{
				logger::error("socket didn't connect to server");
				requestLock.unlock();
				return Json();
			};
			string requestPayload = METHOD_STR[method];
			requestPayload += " " + endpoint;
			requestPayload += " HTTP/1.1\r\n";
			requestPayload += "Host: " + _host;
			if (_port != 80)
				requestPayload += ":" + std::to_string(_port);
			requestPayload += "\r\n";
			requestPayload += "User-Agent: maolib\r\n";
			requestPayload += "Accept: text/plain\r\n";
			requestPayload += "Accept-Language: gzip, deflate, br\r\n";
			requestPayload += "Accept-Encoding: en-US,en;q=0.9,zh-TW;q=0.8,zh;q=0.7,zh-CN;q=0.6\r\n";
			requestPayload += "Connection: keep-alive\r\n";
			if (payload != nullptr)
			{
				requestPayload += "Content-Type: application/json; charset=utf-8\r\n";
				requestPayload += "Content-Length: " + to_string(payload->getJsonString().length()) + "\r\n";
				requestPayload += "\r\n";
				requestPayload += payload->getJsonString();
			}
			requestPayload += "\r\n\r\n";

			if (send(_socket, requestPayload.c_str(), strlen(requestPayload.c_str()), 0) < 0)
			{
				logger::error("Send failed");
				requestLock.unlock();
				return Json();
			}

			string response = "";
			char recvBuff[4096];
			int recvLen = 0;
			do
			{
				recvLen = recv(_socket, recvBuff, 4096, 0);
				response.append(recvBuff, recvLen);
				if (recvLen > 4 && recvBuff[recvLen - 1] == '\n' && recvBuff[recvLen - 2] == '\r' && recvBuff[recvLen - 3] == '\n' && recvBuff[recvLen - 4] == '\r')
					break;

			} while (recvLen > 0);
			requestLock.unlock();
			return parseResponse(response);
		}
		std::thread* OpenApiClient::RequestSync(REQUEST_METHOD method, string endpoint, Json *payload, void (*callback)(Json))
		{
			return new std::thread([=](){			
				Json response=Request(method, endpoint, payload);
				(*callback)(response);
			});
		}
		Json OpenApiClient::parseResponse(string response)
		{
			string line = response.substr(0, response.find("\r\n") + 1);
			if (line.size() == 0 || line.find(' ') < 0)
			{
				logger::error("response wrong data");
				return Json();
			}
			line = line.substr(line.find(' ') + 1);
			string code = line.substr(0, 3);
			if (code != "200")
			{
				logger::error(line);
				return Json();
			}
			string chunks = response.substr(response.find("\r\n\r\n") + 4);
			//logger::debug(line);
			int chunkLen = 0;
			string json = "";
			do
			{
				line = chunks.substr(0, chunks.find("\r\n"));
				chunkLen = stoi(line, 0, 16);
				json += chunks.substr(chunks.find("\r\n") + 2, chunkLen);
				chunks = chunks.substr(chunks.find("\r\n")  + chunkLen+ 4);
			} while (chunkLen != 0);
			return Json(json);
		}
		void OpenApiClient::Dispose()
		{
			if (isConnected)
			{
				close(_socket);
			}
			isConnected = false;
		}
	}
}