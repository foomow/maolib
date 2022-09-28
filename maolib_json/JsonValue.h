#pragma once
#include <list>
#include <string>
using namespace std;
#define _TO_NEXT trim_space(charlist); if (charlist.empty())throw "syntax error";
#define _TO_END trim_space(charlist); if (!charlist.empty())throw "syntax error";
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
		class JsonValue
		{
		public:
			explicit JsonValue() {
				_type = J_NULL;
				_json_string = "null";
			}
			inline J_TYPE getType() {
				return _type;
			}
			string getJsonString();
			void parse(string json);
			friend class JsonObject;
		protected:
			J_TYPE _type;
			string _json_string;
			virtual void parse_value(list<char>& charlist);
			inline string parse_string(list<char>& charlist) {
				_TO_NEXT;
				if (charlist.front() != '\"')throw "syntax error";
				charlist.pop_front();
				string ret = "";
				char last_char = '\0';
				while (charlist.front() != '\"' && last_char != '\\') {
					last_char = charlist.front();
					ret += last_char;
					charlist.pop_front();
					if (charlist.empty())throw "syntax error";
				}
				charlist.pop_front();
				return ret;
			}
			inline string parse_number(list<char>& charlist) {
				_TO_NEXT;
				if (charlist.front() < '0' || charlist.front() > '9')throw "syntax error";
				string ret = "";
				bool hasdot = false;
				do {
					if (charlist.front() == '.') {
						if (hasdot)throw "syntax error";
						hasdot = true;
					}
					ret += charlist.front();
					charlist.pop_front();
				} while ((charlist.front() >= '0' && charlist.front() <= '9') || charlist.front() == '.');
				return ret;
			}
			inline static void trim_space(list<char>& charlist) {
				list<char>::iterator it = charlist.begin();
				while (it != charlist.end()) {
					if (*it != ' ' && *it != '\r' && *it != '\n' && *it != '\t') break;
					it++;
					charlist.pop_front();
				}
			}

		};
	}
}

