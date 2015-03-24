#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>


enum BuiltinType {
	INTEGER, 	// 32 bit integer
	FLOAT,		// 32 bit float


	TYPE_UNKNOWN
};


enum Keyword {
	END,


	NOT_KEYWORD
};

enum Operator {
	PLUS,
	MINUS,
	MULT,
	DIV,

	EQUALS,


	NOT_OP
};



// defined in main.cpp
BuiltinType typeLookup(std::string data);
Keyword keywordLookup(std::string data);
Operator operatorLookup(std::string data);

// get the next character in the source file
// also define in main.cpp, allows the source to come from different places
char getSourceChar();
std::string getTokenSource();

bool isInteger(const std::string &data); 
bool isSymbol(const std::string &data);
// isFloat also returns true if there isn't a decimal afterwards,
// so check with isInteger first, as isInteger will fail for float values
bool isFloat(const std::string &data);

// in place string trimming
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);





#endif // BUILTINS_H