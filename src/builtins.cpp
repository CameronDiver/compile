#include "builtins.h"

#include <cctype>
#include <algorithm>
#include <sstream>

bool isInteger(const std::string &data) {
	return std::all_of(data.begin(), data.end(), static_cast<int(*)(int)>(std::isdigit));
}

bool isSymbol(const std::string &data) {
	// FIXME: Change this code to accept more things for symbols, not just alpha chars
	return std::all_of(data.begin(), data.end(), static_cast<int(*)(int)>(std::isalpha));
}

bool isFloat(const std::string &data) {
	// apparently std::regex isn't supported on linux/gcc
	
	// std::regex reg("[0-9]+.[0-9]+");
	// if(std::regex_match(data, reg)) return true;
	// return false;
	// 
	std::istringstream iss(data);
    float f;
    iss >> std::noskipws >> f;
    return iss && iss.eof();
}

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

std::ostream& operator<<(std::ostream &out, const BuiltinType type){
	const char *s = 0;
	#define SWITCH_STRING(a) case(a): s = #a; break;
	switch(type){
		SWITCH_STRING(INTEGER);
		SWITCH_STRING(FLOAT);
		SWITCH_STRING(TYPE_UNKNOWN);
	}
	#undef SWITCH_STRING

	return out << s;
}
