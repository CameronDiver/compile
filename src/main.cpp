#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "builtins.h"
#include "token.h"

static std::map<std::string, BuiltinType> 	types;
static std::map<std::string, Keyword>		keywords;
static std::map<std::string, Operator>		operators;

static std::ifstream file;
static std::string filename;

void installTypes() {
	types.insert(std::pair<std::string, BuiltinType>("int", INTEGER));
	types.insert(std::pair<std::string, BuiltinType>("float", FLOAT));
}

void installKeywords() {
	keywords.insert(std::pair<std::string, Keyword>("end", END));
}

void installOperators() {
	operators.insert(std::pair<std::string, Operator>("+", PLUS));
	operators.insert(std::pair<std::string, Operator>("-", MINUS));
	operators.insert(std::pair<std::string, Operator>("*", MULT));
	operators.insert(std::pair<std::string, Operator>("/", DIV));
	operators.insert(std::pair<std::string, Operator>("=", DIV));
}

BuiltinType typeLookup(std::string name) {
	if(types.find(name) == types.end())
		return TYPE_UNKNOWN;
	else 
		return types.at(name);
}

Keyword keywordLookup(std::string name) {
	if(keywords.find(name) == keywords.end())
		return NOT_KEYWORD;
	else
		return keywords.at(name);
}

Operator operatorLookup(std::string name) {
	if(operators.find(name) == operators.end())
		return NOT_OP;
	else
		return operators.at(name);
}


char getSourceChar() {
	return file.get();
}

std::string getTokenSource() {
	return filename;
}

int main(int argc, char *argv[]) {
	// intialisation
	installTypes();
	installKeywords();
	installOperators();

	if(argc < 2) {
		std::cout << "Error: Need input file" << std::endl;
		return -1;
	}

	filename = argv[1];

	// Open the file so that the tokeniser can read the characters
	file.open(filename, std::ifstream::in);

	std::vector<Token> tokens;
	if(!Token::tokenize(tokens)) {
		std::cout << "Error: error tokenizing input" << std::endl;
		return -1;
	}



}