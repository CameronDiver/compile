#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

class Token {
public:
	enum Type {
		KEYWORD,
		INT_LITERAL,
		FLOAT_LITERAL,

		SYMBOL,

		SEPERATOR,
		OPERATOR,
		ARG_LIST_CONTAINER,
		OPEN_PAREN,
		CLOSE_PAREN,

		DELIMETER,

		TYPE_NAME,

		END,

		TOKEN_UNKNOWN
	};


	// create a token and attempt to work out it's type just from the string
	// also provide filename and line number for debugging purposes
	Token(std::string data, std::string filename, int line);

	// Create a token but provide a type anyway, useful for when it is known
	// in advance
	Token(std::string data, Type t, std::string file, int _line)
	: strData(data), type(t), filename(file), line(_line) {}


	Type getType();

	static bool tokenize(std::vector<Token> &tokens);

	// the token as a string
	std::string strData;
	Type type;
	std::string filename;
	int line;


private:
	Type getTypeFromString(std::string data);
	static bool isOperatorChar(char c);


};

// function definition to be able to print type names
std::ostream& operator<<(std::ostream& out, const Token::Type t);

#endif // TOKEN_H
