#include <iostream>
#include <vector>
#include <sstream>
#include <any>

std::vector<std::any> StringSplit(const std::string &s, char delimiter) {
	std::vector<std::any> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}