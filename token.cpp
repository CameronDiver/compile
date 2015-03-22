#include "token.h"

Token::Token(string data, int line, string context) {
	this->data = data;
	this->lineno = line;
	this->context = context;
}

Token::Token(string data) {
	this->data = data;
	lineno = 1;
	context = "Unknown context";
}

string Token::getData() {
	return data;
}
const char *Token::getCData() {
	return data.c_str();
}

unsigned int Token::getLine() {
	return lineno;
}