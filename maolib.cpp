#include "maolib.h"
using namespace std;
using namespace maolib;
using namespace maolib::json;
using namespace maolib::time;
int main()
{
	cout << "nihao chengdu" << endl;
	cout << get_now_string() << endl;
	JsonObject a;
	a.parse("{\"a\":  {\"b\":\"nihao\"}}");
	cout << a.getJsonString() << endl;
}