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

	while((t = getCurrentToken()) != NULL) {
		// TODO: check that the first token is a type name, otherwise syntax error,
		// or the parsing is broken somehow

		Expression *primary = parseTopLevelStatement();
		if(primary == NULL) {
			std::cout << "Error: astbuilder.cpp:24" << std::endl;
		} else {
			tree.push_back(primary);
		}

		if(peekNextToken() == NULL) break;
	}

	for(int a = 0; a < tree.size(); ++a) {
		Expression *e = tree[a];
		std::cout << "String representation: " <<  e->getStrRep() << std::endl;
	}
}

Expression *ASTBuilder::parseTopLevelStatement() {
	// get the type 
	Token *type = getNextToken();
	if(type == NULL) return NULL;

	Token *symbolName = getCurrentToken();
	if(symbolName == NULL) return NULL;

	if(!isSymbol(symbolName->getData())) {
		cout << "Error: astbuilder.cpp:33" << endl;
	}

	// next need to check what comes after, 
	// an equals => variable assigment,
	// an argument list => function definition,
	// another typename => variable definition w/out assigment
	Token *next = peekNextToken();

	// there's not another token
	if(next == NULL) {
		
		return new VarExpression(symbolName->getData());
	}else if(!next->getData().compare("=")) {
		

		getNextToken(); // eat the name
		Token *t = getNextToken(); // and the '='

		return new BinaryExpression('=', new VarExpression(symbolName->getData()), parseExpression());

	} else if(!next->getData().compare("|")) {
		
		return parseFunctionDefinition();
		
	} else if(isBuiltinTypeName(next->getData())) {
		getNextToken();
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
	if(!data.compare("(")) return parseParensExpression();

	return NULL;
}

Expression *ASTBuilder::parseFunctionDefinition() {
	// gather the name, the arguments and the body
	std::string fnName = getNextToken()->getData();

	// TODO: sanity checking 

	Token *t = getNextToken();
	cout << t->getData() << endl;
	if(t->getData().compare("|") != 0) {
		cout << "Error: astbuilder.cpp:157" << endl;
	}
	t = getNextToken();
	vector<std::string> args;

	// simple error checking
	int commas = 0;
	while(t != NULL && t->getData().compare("|") != 0) {
		std::string data = t->getData();
		if(t->getData().compare(",") == 0){
			++commas;
		} else {
			// ensure that it can be a variable name
			if(!isSymbol(data)){
				cout << "Error: astbuilder.cpp:171" << endl;
			}
			args.push_back(data);
		}

		t = getNextToken();
	}

	if(args.size() != (commas + 1)) {
		cout << "Error: astbuilder.cpp:180" << endl;
	}

	// create a prototype 
	PrototypeExpression *proto = new PrototypeExpression(fnName, args);


	// now need to get all of the body functions
	// can have function calls and assigments
	
	// the current token is the closing | around the arguments
	t = getNextToken();
	bool endFound = false;
	while(t != NULL) {
		std::string data = t->getData();

		if(data.compare("end") == 0){
			// end of the function definition
			endFound = true;
			break;
		}

		t = getNextToken();
	}
	
	return proto;
}