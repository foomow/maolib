#include "maolib.h"
using namespace std;
using namespace maolib;
int main()
{
	cout << "nihao chengdu" << endl;
	Json a;
	a.test();
	OpenApiClient b;
	b.test();

	cout << time::get_now_string() << endl;
}