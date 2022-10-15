#include "maolib_openapi.h"
#include "../maolib_logger/maolib_logger.h"
#include "../maolib_socket/maolib_socket.h"
using namespace maolib::client_socket;
namespace maolib
{
	namespace openapi
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
				close_socket(_socket);
			}

			isConnected = false;
		}
		bool OpenApiClient::Connect(string host, int port)
		{
			if (isConnected)
			{
				close_socket(_socket);
			}

			isConnected = false;
			_socket = client_socket::connect(host, port);

			if (_socket == -1)
			{
				logger::error("Could not create socket");
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

			if (send(_socket, requestPayload) < 0)
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
				recvLen = recv(_socket, recvBuff, 4096);
				response.append(recvBuff, recvLen);
				if (response.find("\r\n\r\n") >= 0) {
					int linepos = 0;
					do {
						int endpos = response.find("\r\n",linepos) + 2;
						string line = response.substr(linepos, endpos-linepos);
						if (line._Starts_with("Content-Length")) {
							string len = line.substr(line.find(":") + 1);
							int length = stoi(len);
						}
						linepos = endpos ;
					} while (linepos>=0);
				}
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
				close_socket(_socket);
			}
			isConnected = false;
		}
	}
}