#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token {
public:
	Token(string data, int line, string context);
	Token(string data);

	string getData();
	const char *getCData();

	unsigned int getLine();

private:
	// the raw token data (the string)
	string data;
	// the line on which it was found
	int lineno;
	// a human readable context, usually the file in which it resides
	string context;
};


#endif /* TOKEN_H */