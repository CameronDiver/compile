#include "astbuilder.h"

#include <iostream>

ASTBuilder::ASTBuilder(std::vector<Token> &tokens) {
	this->tokens = &tokens;
	tokenIdx = 0;


	parse();
}

void ASTBuilder::parse() {
	// parse top level stuff 
	// either variable declaration/assignment or function definition
	Token *t;

	while((t = getCurrentToken())) {
		// TODO: check that the first token is a type name, otherwise syntax error,
		// or the parsing is broken somehow

		parseTopLevelStatement();

	}
}

Expression *ASTBuilder::parseTopLevelStatement() {
	// get the type 
	Token *type = getNextToken();
	Token *symbolName = getNextToken();

	cout << symbolName->getData() << endl;
	if(!isSymbol(symbolName->getData())) {
		cout << "Error: astbuilder.cpp:33" << endl;
	}

	// next need to check what comes after, 
	// an equals => variable assigment,
	// an argument list => function definition,
	// another typename => variable definition w/out assigment
	Token *next = peekNextToken();
	if(!next->getData().compare("=")) {
		getNextToken(); //eat the =
		return new BinaryExpression('=', new VarExpression(symbolName->getData()), parseExpression());
	} else if(!next->getData().compare("|")) {
		cout << "TODO: function definiton" << endl;
	} else {
		return new VarExpression(symbolName->getData());
	}


	return NULL;
}

// expects the current token to be an integer
Expression *ASTBuilder::parseIntegerExpression() {
	Token *t = getNextToken(); // eat the number token

	IntExpression *expr = new IntExpression(stringToInteger(t->getData()));
	getNextToken();

	return expr;
}

Expression *ASTBuilder::parseParensExpression() {
	getNextToken(); // eat the (
	Expression *e = parseExpression();

	if(!e) return NULL;

	Token *t = getNextToken(); // eat )
	if(t->getData().compare(")") != 0) {
		return NULL;
	}

	return e;
}

Expression *ASTBuilder::parseIdentifierExpression() {
	std::string ident = getNextToken()->getData();

	if(getCurrentToken()->getData().compare("(")) {
		// function call
		// get all of the arguments
		std::vector<Expression *> args;

		getNextToken(); // eat the open bracket
		Token *t = getNextToken();
		while(t != NULL && t->getData().compare(")") != 0) {

			Expression *e = parseExpression();
			if(e == NULL)
				return NULL;

			args.push_back(e);

			t = getCurrentToken();
			if(t->getData().compare(",") != 0) {
				cout << "Error: astbuilder.h:96" << endl;
			}

			t = getNextToken();	
		}

		return new CallExpression(ident, args);
	} else {
		// reference to a variable
		return new VarExpression(ident);
	}

}

Expression *ASTBuilder::parseExpression() {
	Token *t = getCurrentToken();
	std::string data = t->getData();

	if(isSymbol(data)) return parseIdentifierExpression();
	if(isInteger(data)) return parseIntegerExpression();
	if(data[0] == ')') return parseParensExpression();
}

unsigned int ASTBuilder::getTokenType(const Token &t) {

}