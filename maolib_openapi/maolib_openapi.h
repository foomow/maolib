#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "../maolib_json/maolib_json.h"
using namespace std;
using namespace maolib::json;
namespace maolib
{
	namespace openapi
	{
		enum REQUEST_METHOD
		{
			POST,
			PUT,
			GET,
			PATCH,
			DELETE,
			OPTIONS,
			HEAD,
			TRACE
		};
		
		class OpenApiClient
		{
		public:
			OpenApiClient();
			~OpenApiClient();
			bool Connect(string host,int port=80);
			Json Request(REQUEST_METHOD method, string endpoint, Json *payload = nullptr);
			std::thread* RequestSync(REQUEST_METHOD method, string endpoint, Json *payload = nullptr, void (*callback)(Json) = nullptr);
			void Dispose();

		private:
			int _socket;
			string _host;
			int _port;
			bool isConnected;
			thread* pRecvThread;
			void recvThread();
			Json parseChunkedResponse(string response);
			std::mutex requestLock;
		};
	}
}