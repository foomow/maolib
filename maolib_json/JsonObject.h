#pragma once
#include "JsonValue.h"
#include <list>
#include <map>
#include <string>
using namespace std;
namespace maolib {
	namespace json {
		class JsonObject:public JsonValue
		{
		public:
			explicit JsonObject() {
				_type = J_OBJECT;
				_json_string = "{}";
			}
			inline J_TYPE getType() {
				return _type;
			}
			friend class JsonValue;
		protected:
			J_TYPE _type;
			string _json_string;			
			map<string, JsonValue*> _members;
			void parse_value (list<char>& charlist)override;
			void parse_object(list<char>& charlist);
		};
	}
}

