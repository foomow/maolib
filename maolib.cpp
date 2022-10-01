#include "maolib.h"
using namespace std;
using namespace maolib;
using namespace maolib::json;
using namespace maolib::time;
int main(){
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
	a.Insert(b,0);
	cout << a.getJsonString() << endl;
	cout << a.Size() << endl;
}