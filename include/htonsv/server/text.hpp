#ifndef TEXT_HPP
#define TEXT_HPP

#include <vector>
#include <string>

namespace Text {
	inline std::vector<std::string> split(const std::string& text, const std::string& delimiter) {
		std::vector<std::string> result;
		unsigned int delimiter_length = delimiter.length();

		if (!text.length()) return result;

		std::string block;
		std::string region;
		int index = 0;

		for (size_t i = 0; i < text.length(); i++) {
			block = text.substr(i, delimiter_length);
			if (block.length() != delimiter_length) continue;

			if (block == delimiter) {
				region = text.substr(index, i - index);
				result.push_back(region);
				index = i + delimiter_length;
			}
		}

		if (!result.size()) {
			result.push_back(text);
			return result;
		}

		std::string tail = text.substr(index, delimiter_length - index);
		if (tail.length()) result.push_back(tail);

		return result;
	}
};

#endif