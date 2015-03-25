#include "token.h"

#include "builtins.h"

Token::Token(std::string data, std::string file, int _line){
	strData = data;
	filename = file;
	line = _line;
	type = getTypeFromString(data);
}

Token::Type Token::getType() {
	return type;
}

Token::Type Token::getTypeFromString(std::string data) {
	// check if it's a reserved keyword 
	if(keywordLookup(data) != NOT_KEYWORD) return KEYWORD;
	
	// followed by a reserved type name
	if(typeLookup(data) != TYPE_UNKNOWN) return TYPE_NAME;
	
	if(operatorLookup(data) != NOT_OP) return OPERATOR;

	// if not check it's an integer or float literal
	if(isInteger(data)) return INT_LITERAL;

	if(isFloat(data)) return FLOAT_LITERAL;

	if(data.compare(",") == 0) return SEPERATOR;

	if(data.compare("|") == 0) return ARG_LIST_CONTAINER;

	if(data.compare("(") == 0) return OPEN_PAREN;

	if(data.compare(")") == 0) return CLOSE_PAREN;

	if(data.compare(";") == 0) return DELIMETER;

	// if none of those passed, test for it being a generic symbol, if it
	// isn't then pass an unknown
	if(isSymbol(data)) return SYMBOL;
	
	return TOKEN_UNKNOWN;
}

// helper function
static inline void addIfNotEmpty(std::vector<Token> &tokens, std::stringstream &ss, int line) {
	std::string str = ss.str();
	str = trim(str);

	if(str.length() != 0) {
		std::cout << "Adding Token: " << str << " " << getTokenSource() << ":" << line << std::endl;
		Token t(str, getTokenSource(), line);
		tokens.push_back(t);
	}

	ss.str("");
}

bool Token::tokenize(std::vector<Token> &tokens) {
	char c, lastC = '\0';
	int line = 1;
	std::stringstream ss;
	while((c = getSourceChar()) != EOF) {
		
		switch(c) {
			case '\n':
				addIfNotEmpty(tokens, ss, line);
				ss << ';';
				addIfNotEmpty(tokens, ss, line);
				++line;
			break;	

			break;
			case ' ':
			case '\t':
			case '\r':
				addIfNotEmpty(tokens, ss, line);
			break;

			case ',':
			case '|':
			case '(':
			case ')':
			case ';':
				//FIXME: Make another helper function which allows sending what type of
				//token this is to avoid having to re-work it out
				addIfNotEmpty(tokens, ss, line);

				ss << c;

				addIfNotEmpty(tokens, ss, line);
			break;

			// check if it is an operator
			// TODO: a nicer way than hardcoding them in
			case '+':
			case '-':
			case '*':
			case '/':
			case '=':
				addIfNotEmpty(tokens, ss, line);

				ss << c;

				addIfNotEmpty(tokens, ss, line);
			break;

			default:
				ss << c;
			break;
		}

		lastC = c;
	}

	addIfNotEmpty(tokens, ss, line);
	return true;
}