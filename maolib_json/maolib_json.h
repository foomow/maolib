#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>
#include <exception>
using namespace std;
#define _TO_NEXT trim_space(charlist); if (charlist.empty())throw new exception("syntax error");
#define _TO_END trim_space(charlist); if (!charlist.empty())throw new exception("syntax error");
namespace maolib {
	namespace json {
		enum J_TYPE {
			J_INVALID,
			J_NULL,
			J_STRING,
			J_NUMBER,
			J_OBJECT,
			J_ARRAY
		};
		class Json
		{
		public:
			explicit Json();
			explicit Json(string json_str);
			static Json newObject();
			static Json newArray();
			inline J_TYPE getType();
			inline string getJsonString();
			void parse(string json);
			Json& operator[](string key);
			Json& operator[](size_t idx);
			void operator=(string str);
			void operator=(int n);
			void operator=(long n);
			void operator=(long long n);
			void operator=(double d);
			string toStdString();
			int toInt();
			inline double toDouble();
			long toLong();
			long long toLLong();
			int Append(Json &json);
			int Insert(Json& json,size_t idx);
			void Remove(string key);
			void Remove(size_t idx);
			void Clear();
			size_t Size();
		private:
			explicit Json(list<char>& charlist);
			J_TYPE _type;
			string _json_string;
			map<string, Json> _members;
			vector<Json> _elements;
			void init();
			void trim_space(list<char>& charlist);
			void make_json_string();
			void parse_value(list<char>& charlist);
			string parse_string(list<char>& charlist);
			string parse_number(list<char>& charlist);
			void parse_object(list<char>& charlist);
			void parse_array(list<char>& charlist);
		};
	}
}

