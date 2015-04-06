#include "ast.h"

#include <cstdlib>

AbstractSyntaxTree::AbstractSyntaxTree(std::vector<Token> &tokens) {
	// while there is tokens left, attempt to parse them as a top level statement
	this->tokens = tokens;
	currentToken = &tokens[0];
	
	while(currentToken != NULL) {

		if(currentToken->getType() == Token::DELIMETER){
			getNextToken();
			continue;
		}
		FunctionDefinition *fn = parseTopLevel();
		if(fn == NULL) {
			if(currentToken == NULL) {
				// this means that the input has finished
				break;
			}
			// An error occured trying to parse it
			// FIXME: Need error handling
			std::cout << "An error occured" << std::endl;
			exit(EXIT_FAILURE);
		}
#if defined(DEBUG)
		std::cout << fn->prettyPrint() << std::endl;
#endif
		functions.push_back(fn);
	}
}

Token *AbstractSyntaxTree::getNextToken(){
	if((tokenIdx + 1) >= tokens.size()) {
		currentToken = NULL;
		return NULL;
	}

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
	if(currentToken == NULL) return NULL;
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
	FunctionBody *body = parseFunctionBody();
	if(body != NULL)
		return new FunctionDefinition(fnType, name->strData, args, body);
	else
		return NULL;
}

FunctionBody *AbstractSyntaxTree::parseFunctionBody() {
	bool foundEnd = false;
	std::vector<Expression *> statements;

	while(currentToken != NULL && currentToken->getType() == Token::DELIMETER) getNextToken();

	while(currentToken != NULL) {
		// keep looping until we get to an end token
		// we don't have to keep track of how many constructs are 
		// open and count the ends, because the internal parsing
		// functions will keep matching until an end as well, 
		// keeping everything together, unless an end is missing,
		// in which case the while above will fail and it can be detected
		// std::cout << "here parseFunctionBody, token: " << currentToken->getType() 
		// 	<< " - " << currentToken->strData << std::endl;


		if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END) {
			foundEnd = true;
			break;
		}	

		Expression *exp = parseExpression();
		if(exp == NULL) {
			if(currentToken->getType() == Token::DELIMETER) {
				continue;
			} else if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END) {
				foundEnd = true;
				break;
			} else {
				std::cout << "this is the return " << currentToken->getType() << std::endl;
				return NULL;
			}
		} 

		statements.push_back(exp);
	}

	if(!foundEnd){
		error(currentToken, "Couldn't find function end, got ");
		return NULL;
	}
	
	getNextToken(); // eat the 'end'
	return new FunctionBody(statements);
}

Expression *AbstractSyntaxTree::parsePrimaryExpression() {
	// if the first token is a type name it's declaring a variable
	
	// std::cout << "parsePrimaryExpression: " << currentToken->getType()
	// 	<< " - " << currentToken->strData << std::endl;

	switch(currentToken->getType()) {
		// yes I know the breaks are unnecessary but my brain kept
		// on telling me things were falling through so they are 
		// staying
		case Token::TYPE_NAME:
			return parseVariableDeclaration();
		break;
		case Token::INT_LITERAL:
			return parseIntegerLiteral();
		break;
		case Token::FLOAT_LITERAL:
			return parseFloatLiteral();
		break;
		case Token::OPEN_PAREN:
			return parseParenExpression();
		break;
		case Token::SYMBOL:
			return parseIdentifierReference();
		break;
		case Token::DELIMETER:
			getNextToken();
			return NULL;
		break;
		default:
			std::cout << "Error: found unexpected type `"
				<< currentToken->getType() << "' value: '" 
				<< currentToken->strData <<"' at ast.cpp:" << __LINE__ << std::endl;
			return NULL;
		break;
	}
}

Expression *AbstractSyntaxTree::parseExpression() {
	Expression *LHS = parsePrimaryExpression();
	if(LHS == NULL) {
		if(currentToken->getType() == Token::DELIMETER) {
			getNextToken();
			return LHS;
		}
		return NULL;
	}

	return parseBinaryOperationRHS(0, LHS);
}

Expression *AbstractSyntaxTree::parseIdentifierReference() {
	// get the name of the symbol
	std::string name = currentToken->strData;

	// look at the next token to see if it is a open bracket, hence function call
	Token *next = peekNextToken();
	if(next->getType() == Token::OPEN_PAREN) {
		// it's a function call
		return parseFunctionCall();
	} else {
		getNextToken(); // eat the name
		return new SymbolReference(name);
	}
}

Expression *AbstractSyntaxTree::parseFunctionCall() {
	std::string name = currentToken->strData;
	getNextToken();

	if(currentToken->getType() != Token::OPEN_PAREN) {
		error(currentToken, "Expected ( for function call, got");
		return NULL;
	}
	getNextToken();
	std::vector<Expression *> args;
	if(currentToken->getType() != Token::CLOSE_PAREN) {
		while(true) {
			Expression *e = parseExpression();
			if(e == NULL) return NULL;
			args.push_back(e);

			if(currentToken->getType() == Token::CLOSE_PAREN) break;
			if(currentToken->getType() != Token::SEPERATOR) {
				error(currentToken, "Expected argument list seperator (',') or argument list end token (')'), got");
				return NULL;
			}
			getNextToken();
		}
	}
	// eat the close bracket
	// TODO: check it is a close bracket
	getNextToken();
	
	return new Call(name, args);	
}

Expression *AbstractSyntaxTree::parseBinaryOperationRHS(unsigned int minPrec, Expression *LHS) {

	// if it's a closing bracket return
	if(currentToken->getType() == Token::CLOSE_PAREN) return LHS;

	// if it is a binary operation find the precedence
	while(true) {

		if(currentToken->getType() == Token::DELIMETER) {
			getNextToken(); // eat it
			return LHS;
		} 

		// TODO: ensure this gives something meaningful
		Operator op = operatorLookup(currentToken->strData);
		unsigned int prec = precedenceLookup(op);

		if(prec < minPrec) return LHS;

		getNextToken(); // eat operator

		Expression *RHS = parsePrimaryExpression();
		if(RHS == NULL) { 
			if(currentToken->getType() == Token::DELIMETER) {
				getNextToken();
				return LHS;
			}
			return NULL;
		}

		// current token is now either a delimeter or operator
		if(currentToken->getType() == Token::OPERATOR) {
			Operator op2 = operatorLookup(currentToken->strData);
			unsigned int prec2 = precedenceLookup(op2);

			if(prec2 > prec) {
				RHS = parseBinaryOperationRHS(prec + 1, RHS);
				if(RHS == NULL) {
					if(currentToken->getType() == Token::DELIMETER)
						return LHS;
					return NULL;
				}
			}
		}

		LHS = new BinaryOperation(LHS, op, RHS);
	}
}

Expression *AbstractSyntaxTree::parseParenExpression() {
	getNextToken(); // consume the (
	Expression *e = parseExpression();
	if(e == NULL) return NULL;

	if(currentToken->getType() != Token::CLOSE_PAREN) {
		error(currentToken, "Expected ')', got");
		return NULL;
	}
	getNextToken(); // eat )
	return e;
}

Expression *AbstractSyntaxTree::parseIntegerLiteral() {
	Expression *e = new IntLiteral(stoi(currentToken->strData));
	getNextToken(); // eat the literal
	return e;
}

Expression *AbstractSyntaxTree::parseFloatLiteral() {
	Expression *e = new FloatLiteral(stof(currentToken->strData));
	getNextToken(); // consume the token
	return e;
}

Expression *AbstractSyntaxTree::parseVariableDeclaration() {
	// get the type name first
	BuiltinType t = typeLookup(currentToken->strData);
	if(t == TYPE_UNKNOWN) {
		error(currentToken, "Unknown type name");
		return NULL;
	}

	getNextToken();
	if(currentToken->getType() != Token::SYMBOL) {
		error(currentToken, "Expected valid identifier, got");
		return NULL;
	}
	std::string name = currentToken->strData;


	// if there is an equals operator afterward, it means that
	// this is an assigment, and the top level is actually an initialisation
	Token *next = peekNextToken();
	if(next != NULL && next->getType() == Token::OPERATOR && next->strData.compare("=") == 0) {
		getNextToken(); //currentToken is now the =
		getNextToken();
		return new VariableInitialisation(t, name, parseExpression());
	} else {
		// If the next token isn't an equals then it must be a delimiter
		if(next->getType() != Token::DELIMETER) {
			error(next, "Expected '=' or delimiter (';' or '\\n'), got");
			return NULL;
		}
		return new VariableDeclaration(t, name);
	}
}

void AbstractSyntaxTree::error(Token *t, std::string message) {
	std::cout << "Error: " << message << " `" << t->strData
			<< "' [" << t->filename << ":"
			<< t->line << "]" << std::endl;
}