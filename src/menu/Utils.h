#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>
#include <vector>
#include <string>

using std::string;
using std::vector;

class Utils {
public:
	Utils();
	~Utils();
	static string intToString(int i);
	static int stringToInt(string s);
	static bool isANumber(string s);
	static void split(string text, string delim, vector<string>* tokens);
};

#endif /* UTILS_H_ */