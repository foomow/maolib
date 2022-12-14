#include "maolib.h"
using namespace std;
using namespace maolib;
using namespace maolib::json;
using namespace maolib::time;

struct test_type
{
	int n;
	std::string s;
	vector<int> il;
	vector<string> sl;
	long x;
};
SETUP_DESERIALIZER(test_type, n, s, il, sl, x)
struct test_type1
{
	int n;
	std::string s;
	vector<int> il;
	vector<string> sl;
	long x;
};
int main()
{
	maolib::logger::init();
	Json j("{\"n\":1,\"s\":\"nihao chengdu\",\"il\":[1,2,3,4,5,6],\"sl\":[\"sss\",\"ttt\"],\"x\":8768}");
	test_type je;
	DESERIALIZE(test_type, j, &je);
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
	openapi::OpenApiClient client;
#ifdef __linux__
	client.Connect("api.localhost");
	Json payload("\"111\"");
	Json reponse = client.Request(openapi::GET, "/WeatherForecast", &payload);
	maolib::logger::info(reponse.getJsonString());

	std::thread *x = client.RequestSync(openapi::GET, "/WeatherForecast", &payload, [](Json reponse)
										{ maolib::logger::info(reponse.getJsonString()); });
	x->join();

	maolib::redis::redis_client redis_client("172.20.0.3");
	redis_client.ConnectSub();
	redis_client.PSubscribe("__keyspace@0__:test*", [](Json ret)
							{ maolib::logger::info("notify:"+ret.getJsonString()); });
	redis_client.ConnectCmd();
	maolib::json::Json res = redis_client.ExcuteCommand("set test123 'nihao chengdu. im \"mao\"'");
	maolib::logger::info(res.getJsonString());
	maolib::logger::info(res.getJsonString());
	res = redis_client.ExcuteCommand("keys *");
	maolib::logger::info(res.getJsonString());
	res = redis_client.ExcuteCommand("get test");
	maolib::logger::info(res.getJsonString());
	this_thread::sleep_for(std::chrono::milliseconds(300));
	redis_client.CloseCmd();
	redis_client.CloseSub();
#else
	client.Connect("restapi.adequateshop.com");
	Json payload("\"111\"");
	Json reponse = client.Request(openapi::GET, "/api/Tourist?page=1", &payload);
	maolib::logger::info(reponse.getJsonString());

	std::thread *x = client.RequestSync(openapi::GET, "/api/Tourist?page=1", &payload, [](Json reponse)
										{ maolib::logger::info(reponse.getJsonString()); });
	x->join();
#endif // DEBUG
	maolib::logger::dispose();
}