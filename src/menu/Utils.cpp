#include <iostream>
#include "Utils.h"

Utils::Utils() {
}

Utils::~Utils() {
}

std::string Utils::intToString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

int Utils::stringToInt(string s) {
	int e;
	std::stringstream ss(s);
	ss >> e;
	return e;
}

bool Utils::isANumber(string s) {
	int d;
	std::stringstream ss(s);
	ss >> d;
	string str = intToString(d);
	return !ss.fail() && (s == str);
}

void Utils::split(string text, string delim, std::vector<string>* tokens) {
	unsigned int lastPos = 0;
	unsigned int currPos = text.find(delim, lastPos);

	while(currPos != string::npos) {
		tokens->push_back(text.substr(lastPos, currPos-lastPos));
		lastPos = currPos + delim.length();
		currPos = text.find(delim, lastPos);
	}

	string single = text.substr(lastPos, text.length());
	if(single.length() > 0)
		tokens->push_back(single);
}
