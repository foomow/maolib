#include "JsonValue.h"
#include "JsonObject.h"
#include <typeinfo>
namespace maolib {
	namespace json {
		void JsonValue::parse(string json)
		{
			list<char> charlist(json.begin(), json.end());
			_TO_NEXT;
			parse_value(charlist);
			_TO_END;
		}
		void JsonValue::parse_value(list<char>& charlist)
		{
			_TO_NEXT;
			switch (charlist.front()) {
			case '\"':
				_type = J_STRING;
				_json_string = parse_string(charlist);
				break;
			case 'n':
				_type = J_NULL;
				_json_string = "null";
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				_type = J_NUMBER;
				_json_string = parse_number(charlist);
				break;
			default:
				throw "syntax error";
				break;
			}
		}
		string JsonValue::getJsonString() {
			string ret = "";
			switch (_type) {
			case maolib::json::J_INVALID:
				break;
			case maolib::json::J_NULL:
				return "null";
				break;
			case maolib::json::J_STRING:
				return "\"" + _json_string + "\"";
				break;
			case maolib::json::J_NUMBER:
				return  _json_string;
				break;
			case maolib::json::J_OBJECT:
				break;
			case maolib::json::J_ARRAY:
				break;
			default:
				break;
			}
			return ret;
		}
	}
}
