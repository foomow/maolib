#include "maolib_openapi.h"
namespace maolib
{
	namespace OpenApiClient
	{

		OpenApiClient::OpenApiClient()
		{
		}
		OpenApiClient::~OpenApiClient()
		{
		}
		bool OpenApiClient::Connect(string url)
		{
			return false;
		}
		Json OpenApiClient::Request(REQUEST_METHOD method, string endpoint, Json *payload)
		{
			return Json();
		}
		void OpenApiClient::Dispose() {}
	}
}