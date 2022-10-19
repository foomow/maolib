#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace maolib
{
	namespace utils
	{
		// replace all text with new text in a string.
		std::string string_replace(std::string str, const std::string &text, const std::string &new_text);
		// split a string with separator to a vector.
		std::vector<std::string> string_split(const std::string& str, char separator);
		//check if a str start with pattern
		bool string_starts_with(std::string str, std::string pattern);
	}
}
