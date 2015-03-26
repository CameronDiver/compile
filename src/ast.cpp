#include "ast.h"

#include <cstdlib>

AbstractSyntaxTree::AbstractSyntaxTree(std::vector<Token> &tokens) {
	// while there is tokens left, attempt to parse them as a top level statement
	this->tokens = tokens;
	currentToken = &tokens[0];
	
	while(currentToken != NULL) {
		FunctionDefinition *fn = parseTopLevel();
		if(fn == NULL) {
			// An error occured trying to parse it
			// FIXME: Need error handling
			std::cout << "An error occured" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << fn->prettyPrint() << std::endl;
		functions.push_back(fn);
	}
}

Token *AbstractSyntaxTree::getNextToken(){
	if(tokenIdx >= tokens.size())
		return NULL;

	++tokenIdx;
	currentToken = &tokens[tokenIdx];
	return currentToken;
}

Token *AbstractSyntaxTree::peekNextToken() {
	if((tokenIdx + 1) >= tokens.size())
		return NULL;
	return &tokens[tokenIdx + 1];
}

FunctionDefinition *AbstractSyntaxTree::parseTopLevel() {
	// first token should be a typename
	if(currentToken->getType() != Token::TYPE_NAME) {
		// error = "Unknown typename"
		error(currentToken, "Unknown type name");
		return NULL;
	}

	BuiltinType fnType = typeLookup(currentToken->strData);
	// TODO: check that it's found something
	
	Token *name = getNextToken();
	if(name->getType() != Token::SYMBOL) {
		error(currentToken, "Invalid function name");
		return NULL;
	}

	// Sanity checking
	if(getNextToken()->getType() != Token::ARG_LIST_CONTAINER) {
		error(currentToken, "Expected argument list start token ('|') but got ");
		return NULL;
	}

	std::vector<ArgPair> args;

	// now go through the argument list and 
	while(currentToken != NULL) {
		getNextToken();
		// currentToken now should either be a typename
		// or Token::ARG_LIST_CONTAINER
		
		if(currentToken->getType() == Token::ARG_LIST_CONTAINER) break;

		// so at this point it must be a typename
		if(currentToken->getType() != Token::TYPE_NAME){
			error(currentToken, "Invalid type name");
			return NULL;
		}
		
		BuiltinType type = typeLookup(currentToken->strData);
		// TODO: checking
		
		getNextToken();

		// now the current token needs to be a valid symbol
		if(currentToken->getType() != Token::SYMBOL){
			error(currentToken, "Expected valid identifier, got ");
			return NULL;
		}

		// we have both the type and the symbol, add them to an argpair
		ArgPair pair(type, currentToken->strData);
		args.push_back(pair);

		// the next token should either be a delimiter or a
		// argument list ending token, otherwise it's a syntax error
		Token *next = peekNextToken();
		// just continue in this case as that will be caught at the top of the while
		if(next->getType() == Token::ARG_LIST_CONTAINER) continue;
		if(next->getType() != Token::SEPERATOR) {
			error(next, "Expected delimiter (',') or argument list token ('|'), got");
			return NULL;
		} else {
			// eat the comma
			getNextToken();
		}
	}

	// eat the closing '|'
	getNextToken();
	return new FunctionDefinition(fnType, name->strData, args, parseFunctionBody());
}

FunctionBody *AbstractSyntaxTree::parseFunctionBody() {
	bool foundEnd = false;
	std::vector<Expression *> statements;

	while(currentToken != NULL) {
		// keep looping until we get to an end token
		// we don't have to keep track of how many constructs are 
		// open and count the ends, because the internal parsing
		// functions will keep matching until an end as well, 
		// keeping everything together, unless an end is missing,
		// in which case the while above will fail and it can be detected
		
		if(currentToken->getType() == Token::END) {
			foundEnd = true;
			break;
		}
	}

	if(!foundEnd){
		error("Couldn't find function end, got ");
		return NULL;
	}
	return NULL;
}

void AbstractSyntaxTree::error(Token *t, std::string message) {
	std::cout << "Error: " << message << " `" << t->strData
			<< "' [" << t->filename << ":"
			<< t->line << "]" << std::endl;
}