#pragma once
#include <iostream>
#include <thread>
#include "../maolib_json/maolib_json.h"
using namespace std;
using namespace maolib::json;
namespace maolib
{
	namespace OpenApiClient
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
			bool Connect(string host);
			Json Request(REQUEST_METHOD method, string endpoint, Json *payload = nullptr);
			void Request(REQUEST_METHOD method, string endpoint, Json *payload = nullptr, void (*callback)(Json) = nullptr);
			void Dispose();

		private:
			int _socket;
			bool isConnected;
			thread* pRecvThread;
			void recvThread();
		};
	}
}