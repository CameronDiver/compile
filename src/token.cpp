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

	if(unaryOperatorLookup(data) != NOT_UNARY) return UNARY_OPERATOR;
	
	// if not check it's an integer or float literal
	if(isInteger(data)) return INT_LITERAL;

	if(isFloat(data)) return FLOAT_LITERAL;

	if(data.compare(",") == 0) return SEPERATOR;

	if(data.compare("|") == 0) return ARG_LIST_CONTAINER;

	if(data.compare("(") == 0) return OPEN_PAREN;

	if(data.compare(")") == 0) return CLOSE_PAREN;

	if(data.compare(";") == 0) 		return DELIMETER;
	if(data.compare("\\n") == 0) 	return DELIMETER;

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
#if defined(DEBUG) 
		//std::cout << "Adding Token: " << str << " " << getTokenSource() << ":" << line << std::endl;
#endif
		Token t(str, getTokenSource(), line);
		tokens.push_back(t);
	}

	ss.str("");
}

bool Token::tokenize(std::vector<Token> &tokens) {
	//char c, lastC = '\0';
	char c = '\0', nextC = getSourceChar();
	int line = 1;
	std::stringstream ss;

	bool comment = false;

	while(nextC != EOF) {
		c = nextC;
		nextC = getSourceChar();

		if(comment) {
			if(c == '\n') {
				comment = false;
			} else continue;
		}


		if(c == '\n') {
			addIfNotEmpty(tokens, ss, line);
			ss << "\\n";
			addIfNotEmpty(tokens, ss, line);
			++line;
		} else if(c == ' ' || c == '\t' || c == '\r') {
			addIfNotEmpty(tokens, ss, line);
		} else if(c == ',' || c == '|' || c == '(' || c == ')' || c == ';') {
			addIfNotEmpty(tokens, ss, line);

			ss << c;

			addIfNotEmpty(tokens, ss, line);
		} else if(isUnaryOperatorChar(c)) {
			addIfNotEmpty(tokens, ss, line);
			ss << c;
			addIfNotEmpty(tokens, ss, line);
		} else if(isOperatorChar(c)) {
			// check nextC to see if it is a double char operator
			if(isOperatorChar(nextC)) {
				// this will be checked to be an actual operator
				// in get type code in this class
				addIfNotEmpty(tokens, ss, line);
				ss << c << nextC;
				addIfNotEmpty(tokens, ss, line);
				nextC = getSourceChar();
			} else {
				addIfNotEmpty(tokens, ss, line);
				ss << c;
				addIfNotEmpty(tokens, ss, line);
			}
		} else if(c == '#') {
			// TODO: check not in string etc
			comment = true;
		} else {
			ss << c;
		}
	}

	addIfNotEmpty(tokens, ss, line);
	return true;
}

bool Token::isOperatorChar(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '=' || c == '<' || c == '>' || c == '%'
		|| c == '&';
}

bool Token::isUnaryOperatorChar(char c) {
	return c == '!' || c == '~';
}

std::ostream& operator<<(std::ostream& out, const Token::Type t) {
	const char *s = 0;

	#define SWITCH_STRING(a) case(a): s = #a; break;
	switch(t){
		SWITCH_STRING(Token::KEYWORD);
		SWITCH_STRING(Token::INT_LITERAL);
		SWITCH_STRING(Token::FLOAT_LITERAL);
		SWITCH_STRING(Token::SYMBOL);
		SWITCH_STRING(Token::SEPERATOR);
		SWITCH_STRING(Token::OPERATOR);
		SWITCH_STRING(Token::ARG_LIST_CONTAINER);
		SWITCH_STRING(Token::OPEN_PAREN);
		SWITCH_STRING(Token::CLOSE_PAREN);
		SWITCH_STRING(Token::DELIMETER);
		SWITCH_STRING(Token::TYPE_NAME);
		SWITCH_STRING(Token::END);
		SWITCH_STRING(Token::UNARY_OPERATOR);
		SWITCH_STRING(Token::TOKEN_UNKNOWN);
	}
	#undef SWITCH_STRING

	return out << s;
}