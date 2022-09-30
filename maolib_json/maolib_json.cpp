#include "maolib_json.h"
namespace maolib {
	namespace json {
		Json::Json() {
			init();
		}
		Json::Json(string json_str) {
			init();
			parse(json_str);
		}
		Json Json::newObject()
		{
			return Json("{}");
		}
		Json Json::newArray()
		{
			return Json("[]");
		}
		J_TYPE Json::getType()
		{
			return _type;
		}
		string Json::getJsonString() {
			make_json_string();
			if (_type == J_STRING)
				return "\"" + _json_string + "\"";
			else
				return _json_string;
		}
		void Json::parse(string json) {
			list<char> charlist(json.begin(), json.end());
			_TO_NEXT;
			parse_value(charlist);
			_TO_END;
		}
		Json& Json::operator[](string key) {
			switch (_type) {
			case maolib::json::J_OBJECT:
				return _members[key];
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		Json& Json::operator[](size_t idx) {
			switch (_type) {
			case J_ARRAY:
				return _elements[idx];
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		void Json::operator=(string str) {
			_type = J_STRING;
			_json_string = str;
			_elements.clear();
			_members.clear();
		}
		void Json::operator=(int n) {
			_type = J_NUMBER;
			_json_string = to_string(n);
			_elements.clear();
			_members.clear();
		}
		void Json::operator=(long n) {
			_type = J_NUMBER;
			_json_string = to_string(n);
			_elements.clear();
			_members.clear();
		}
		void Json::operator=(long long n) {
			_type = J_NUMBER;
			_json_string = to_string(n);
			_elements.clear();
			_members.clear();
		}
		void Json::operator=(double d) {
			_type = J_NUMBER;
			_json_string = to_string(d);
			_elements.clear();
			_members.clear();
		}
		string Json::toStdString() {
			switch (_type) {
			case J_NUMBER:
			case J_STRING:
			case J_NULL:
			case J_INVALID:
				return _json_string;
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		int Json::toInt() {
			switch (_type) {
			case J_NUMBER:
			case J_STRING:
				return stoi(_json_string);
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		double Json::toDouble() {
			switch (_type) {
			case J_NUMBER:
			case J_STRING:
				return stod(_json_string);
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		long Json::toLong() {
			switch (_type) {
			case J_NUMBER:
			case J_STRING:
				return stol(_json_string);
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		long long Json::toLLong() {
			switch (_type) {
			case J_NUMBER:
			case J_STRING:
				return stoll(_json_string);
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		int Json::Append(Json& json) {
			switch (_type) {
			case J_ARRAY:
				_elements.push_back(json);
				return _elements.size();;
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		int Json::Insert(Json& json, size_t idx)
		{
			if (_elements.size() > idx) {
				switch (_type) {
				case J_ARRAY:
					_elements.insert(_elements.begin() + idx, json);
					return _elements.size();
					break;
				default:
					_THROW("invalid operation");
					break;
				}
			}
		}
		void Json::Remove(string key) {
			switch (_type) {
			case J_OBJECT:
				_members.erase(key);
				return;
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		void Json::Remove(size_t idx) {
			if (_elements.size() > idx) {
				switch (_type) {
				case J_ARRAY:
					_elements.erase(_elements.begin() + idx, _elements.begin() + idx + 1);
					return;
					break;
				default:
					_THROW("invalid operation");
					break;
				}
			}
		}
		void Json::Clear() {
			switch (_type) {
			case J_ARRAY:
				_elements.clear();
				return;
				break;
			case J_OBJECT:
				_members.clear();
				return;
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		size_t Json::Size()
		{
			switch (_type) {
			case J_ARRAY:
				return _elements.size();
				break;
			case J_OBJECT:
				return _members.size();
				break;
			case J_STRING:
				return _json_string.size();
				break;
			default:
				_THROW("invalid operation");
				break;
			}
		}
		Json::Json(list<char>& charlist) {
			init();
			_TO_NEXT;
			parse_value(charlist);
		}
		void Json::init() {
			_type = J_NULL;
			_json_string = "null";
			_elements.clear();
			_members.clear();
		}
		void Json::trim_space(list<char>& charlist) {
			list<char>::iterator it = charlist.begin();
			while (it != charlist.end()) {
				if (*it != ' ' && *it != '\r' && *it != '\n' && *it != '\t') break;
				it++;
				charlist.pop_front();
			}
		}
		void Json::make_json_string() {
			switch (_type) {
			case J_INVALID:
				_json_string = "";
				break;
			case J_OBJECT:
				_json_string = "{";
				if (_members.size() > 0) {
					for (pair<string, Json> nv : _members) {
						_json_string += "\"" + nv.first + "\":" + nv.second.getJsonString() + ",";
					}
					*(_json_string.end() - 1) = '}';
				}
				else {
					_json_string += "}";
				}
				break;
			case J_ARRAY:
				_json_string = "[";
				if (_elements.size() > 0) {
					for (Json v : _elements) {
						_json_string += v.getJsonString() + ",";
					}
					*(_json_string.end() - 1) = ']';
				}
				else {
					_json_string += "]";
				}
				break;
			default:
				break;
			}
		}
		void Json::parse_value(list<char>& charlist) {
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
			case '{':
				_type = J_OBJECT;
				parse_object(charlist);
				break;
			case '[':
				_type = J_ARRAY;
				parse_array(charlist);
				break;
			default:
				_THROW("syntax error");
				break;
			}
		}
		string Json::parse_string(list<char>& charlist) {
			_TO_NEXT;
			if (charlist.front() != '\"')_THROW("syntax error");
			charlist.pop_front();
			string ret = "";
			char last_char = '\0';
			while (charlist.front() != '\"' && last_char != '\\') {
				last_char = charlist.front();
				ret += last_char;
				charlist.pop_front();
				if (charlist.empty())_THROW("syntax error");
			}
			charlist.pop_front();
			return ret;
		}
		string Json::parse_number(list<char>& charlist) {
			_TO_NEXT;
			if (charlist.front() < '0' || charlist.front() > '9')_THROW("syntax error");
			string ret = "";
			bool hasdot = false;
			do {
				if (charlist.front() == '.') {
					if (hasdot)_THROW("syntax error");
					hasdot = true;
				}
				ret += charlist.front();
				charlist.pop_front();
			} while ((charlist.front() >= '0' && charlist.front() <= '9') || charlist.front() == '.');
			return ret;
		}
		void Json::parse_object(list<char>& charlist)
		{
			_TO_NEXT;
			if (charlist.front() != '{')_THROW("syntax error");
			charlist.pop_front();
			if (charlist.front() != '}') {
				do {
					_TO_NEXT;
					string name = parse_string(charlist);
					_TO_NEXT;
					if (charlist.front() != ':')_THROW("syntax error");
					charlist.pop_front();
					_TO_NEXT;
					Json value(charlist);
					_members[name] = value;
					_TO_NEXT;
					if (charlist.front() == '}') break;
					if (charlist.front() != ',')_THROW("syntax error");
					charlist.pop_front();
				} while (1);
			}
			charlist.pop_front();
		}
		void Json::parse_array(list<char>& charlist)
		{
			_TO_NEXT;
			if (charlist.front() != '[')_THROW("syntax error");
			charlist.pop_front();
			if (charlist.front() != ']') {
				do {
					_TO_NEXT;
					Json value(charlist);
					_elements.push_back(value);
					_TO_NEXT;
					if (charlist.front() == ']') break;
					if (charlist.front() != ',')_THROW("syntax error");
					charlist.pop_front();
				} while (1);
			}
			charlist.pop_front();
		}
	}
}