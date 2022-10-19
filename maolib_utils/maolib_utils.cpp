#include "maolib_utils.h"

namespace maolib
{
	namespace utils
	{
		std::string string_replace(std::string str, const std::string &text, const std::string &new_text)
		{
			if (!text.empty())
			{
				std::size_t pos = 0;
				while ((pos = str.find(text, pos)) != std::string::npos)
				{
					str.replace(pos, text.length(), new_text);
					pos += new_text.length();
				}
			}
			return str;
		}
		std::vector<std::string> string_split(const std::string &str, char separator)
		{
			std::vector<std::string> els;
			std::string el;
			std::istringstream str_stream(str);
			while (std::getline(str_stream, el, separator))
			{
				els.push_back(el);
			}
			return els;
		}
		bool string_starts_with(std::string str, std::string pattern)
		{
			return str.find(pattern) == 0;
		}
	}
}