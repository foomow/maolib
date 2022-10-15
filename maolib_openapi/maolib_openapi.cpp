#include "maolib_openapi.h"
#include "maolib_openapi.h"
#include "../maolib_logger/maolib_logger.h"
#include "../maolib_socket/maolib_socket.h"
#define BUFFLEN 4096
using namespace maolib::client_socket;
namespace maolib
{
	namespace openapi
	{
		const char* METHOD_STR[8] = {
			"POST",
			"PUT",
			"GET",
			"PATCH",
			"DELETE",
			"OPTIONS",
			"HEAD",
			"TRACE" };
		OpenApiClient::OpenApiClient() : 
			_socket(-1),
			isConnected(false),
			_port(80),
			_host("localhost")
		{
		}
		OpenApiClient::~OpenApiClient()
		{
			if (isConnected) {
				close_socket(_socket);
			}

			isConnected = false;
		}
		bool OpenApiClient::Connect(string host, int port)
		{
			if (isConnected) {
				close_socket(_socket);
			}

			isConnected = false;
			_socket = client_socket::connect(host, port);

			if (_socket == -1) {
				logger::error("Could not create socket");
				return false;
			}

			_host = host;
			_port = port;
			logger::info("Connected");
			isConnected = true;
			return true;
		}
		Json OpenApiClient::Request(REQUEST_METHOD method, string endpoint, Json* payload)
		{
			requestLock.lock();
			if (!isConnected) {
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
			if (payload != nullptr) {
				requestPayload += "Content-Type: application/json; charset=utf-8\r\n";
				requestPayload += "Content-Length: " + to_string(payload->getJsonString().length()) + "\r\n";
				requestPayload += "\r\n";
				requestPayload += payload->getJsonString();
			}
			requestPayload += "\r\n\r\n";

			if (send(_socket, requestPayload) < 0) {
				logger::error("Send failed");
				requestLock.unlock();
				return Json();
			}

			string response = "";
			char recvBuff[BUFFLEN];
			int recvLen = 0;
			do {
				recvLen = recv(_socket, recvBuff, BUFFLEN);
				if (recvLen > 0) {
					response.append(recvBuff, recvLen);
					if (response.find("\r\n\r\n") >= 0) {
						//parse head info to check response status
						string line = response.substr(0, response.find("\r\n") + 1);
						if (line.size() == 0 || line.find(' ') < 0) {
							logger::error("response wrong data");
							requestLock.unlock();
							return Json();
						}
						line = line.substr(line.find(' ') + 1);
						string code = line.substr(0, 3);
						if (code != "200") {
							logger::error(line);
							requestLock.unlock();
							return Json();
						}
						//parse head info to check transfer type
						int linepos = 0;
						do {
							int endpos = response.find("\r\n", linepos) + 2;
							string line = response.substr(linepos, endpos - linepos);
							if (line == "Transfer-Encoding: chunked\r\n") {
								//read all data for chunked content
								bool isFinished = (recvLen > 4 && recvBuff[recvLen - 1] == '\n' && recvBuff[recvLen - 2] == '\r' && recvBuff[recvLen - 3] == '\n' && recvBuff[recvLen - 4] == '\r');
								if (!isFinished) {
									do {
										recvLen = recv(_socket, recvBuff, BUFFLEN);
										response.append(recvBuff, recvLen);
										if (recvLen > 4 && recvBuff[recvLen - 1] == '\n' && recvBuff[recvLen - 2] == '\r' && recvBuff[recvLen - 3] == '\n' && recvBuff[recvLen - 4] == '\r')
											break;

									} while (recvLen > 0);
								}
								requestLock.unlock();
								string chunks = response.substr(response.find("\r\n\r\n") + 4);
								int chunkLen = 0;
								string content = "";
								do {
									string line = chunks.substr(0, chunks.find("\r\n"));
									chunkLen = stoi(line, 0, 16);
									content += chunks.substr(chunks.find("\r\n") + 2, chunkLen);
									chunks = chunks.substr(chunks.find("\r\n") + chunkLen + 4);
								} while (chunkLen != 0);
								return Json(content);
							}
							if (line.substr(0, 15) == "Content-Length:") {
								requestLock.unlock();
								int len = stoi(line.substr(16));
								string content= response.substr(response.find("\r\n\r\n") + 4);
								while (content.length() != len) {
									recvLen = recv(_socket, recvBuff, BUFFLEN);
									content.append(recvBuff, recvLen);
								}
								return Json(content);
							}
							linepos = endpos;
						} while (linepos >= 0);
					}
				}
			} while (recvLen > 0);
			requestLock.unlock();
			return Json();
		}
		std::thread* OpenApiClient::RequestSync(REQUEST_METHOD method, string endpoint, Json* payload, void (*callback)(Json))
		{
			return new std::thread([=]()
				{
					Json response = Request(method, endpoint, payload);
					(*callback)(response); });
		}		
		void OpenApiClient::Dispose()
		{
			if (isConnected) {
				close_socket(_socket);
			}
			isConnected = false;
		}
	}
}