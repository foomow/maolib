#include "maolib.h"
using namespace std;
using namespace maolib;
using namespace maolib::json;
using namespace maolib::time;
int main()
{
	maolib::logger::init();
	logger::debug("debug info");
	cout << "nihao chengdu" << endl;
	cout << get_now_string() << endl;
	Json a;
	a.parse("[1,2,\"nihao\",{\"a\":\"\\nchengdu\\n\"},{\"name\":\"mao\",\"age\":46}]");
	cout << a.getJsonString() << endl;
	cout << a[2].getJsonString() << endl;
	cout << a[3]["ag"].getJsonString() << endl;
	cout << a[4]["age"].toInt() << endl;
	cout << a[4]["name"].toStdString() << endl;
	a[4]["tele"] = "13880438937";
	a[1] = "new str";
	cout << a[1].toStdString() << endl;
	a[0] = 1024;
	cout << a[0].toStdString() << endl;
	cout << a.getJsonString() << endl;
	Json b = Json::newObject();
	a.Insert(b, 2);
	cout << a.getJsonString() << endl;
	b = Json();
	a.Insert(b, 0);
	cout << a.getJsonString() << endl;
	cout << a.Size() << endl;
	OpenApiClient::OpenApiClient client;
	client.Connect("api.localhost");
	Json reponse = client.Request(OpenApiClient::GET, "/WeatherForecast");
	maolib::logger::info(reponse.getJsonString());

	std::vector<std::thread*> pool;
	maolib::logger::debug("begin sent");
	for (int i = 0; i < 60; i++)
	{
		std::thread* x = client.RequestSync(OpenApiClient::GET, "/WeatherForecast", nullptr, [](Json reponse)
									{
										 maolib::logger::info(reponse.getJsonString()); 
									});
									pool.push_back(x);
		maolib::logger::debug("request sent");
		this_thread::sleep_for(chrono::milliseconds(10));
	}	
	maolib::logger::debug("finish sent");
	for(auto x:pool){
		x->join();
	}
	maolib::logger::debug("finish request");
	maolib::logger::dispose();
}