#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
namespace maolib {
	namespace Json {
		enum J_TYPE {
			J_INVALID,
			J_NULL,
			J_NUMBER,
			J_STRING,
			J_ARRAY,
			J_OBJECT
		};

		class JsonValue {
		public:
			inline J_TYPE GetType() { return _type; }
			inline std::string ToString() { return _json_str; }
		private:
			virtual void _parse(std::string json_str);
			J_TYPE _type;
			std::string _json_str;
		};

		class JObject :public JsonValue {
		public:
			JObject();
			~JObject();
		private:
			void _parse(std::string json_str);
			std::map<std::string, JsonValue> _members;
		};

		class JArray :public JsonValue {
		public:
			JArray();
			~JArray();
		private:
			void _parse(std::string json_str);
			std::vector<JsonValue> _members;
		};
	}
}