#include "JsonObject.h"
namespace maolib {
	namespace json {
		void JsonObject::parse_value(list<char>& charlist)
		{
			_TO_NEXT;
			switch (charlist.front()) {			
			case '{':
				parse_object(charlist);
				break;			
			default:
				throw "syntax error";
				break;
			}
		}
		void JsonObject::parse_object(list<char>& charlist)
		{			
			if (charlist.front() != '{')throw "syntax error";
			charlist.pop_front();

			do {
				_TO_NEXT;
				string name = parse_string(charlist);
				_TO_NEXT;
				if (charlist.front() != ':')throw "syntax error";
				charlist.pop_front();
				_TO_NEXT;
				if (charlist.front() == '{') {
					JsonObject value; 
					value.parse_value(charlist);
					_members[name] = value;
				}
				else {
					JsonValue value;
					value.parse_value(charlist);
					_members[name] = value;
				}
				_TO_NEXT;
				if (charlist.front() == '}') break;
				if (charlist.front() != ',')throw "syntax error";
				charlist.pop_front();
			} while (1);
			charlist.pop_front();			
		}
	}
}
