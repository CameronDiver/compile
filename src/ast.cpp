#include "ast.h"

#include <cstdlib>

AbstractSyntaxTree::AbstractSyntaxTree(std::vector<Token> &tokens) {
	// while there is tokens left, attempt to parse them as a top level statement
	this->tokens = tokens;
	currentToken = &tokens[0];
	tokenIdx = 0;
	
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
			std::cout << "An error occured, exiting" << std::endl;
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

	 // if it is an external function declaration
	if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == EXTERN) {
		return parseExtern();
	}
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

FunctionDefinition *AbstractSyntaxTree::parseExtern() {
	// TODO: Check current token is definitely an extern token
	getNextToken();
	if(currentToken == NULL) return NULL;
	
	if(currentToken->getType() != Token::TYPE_NAME) {
		error(currentToken, "Expected typename after extern declaration, got ");
		return NULL;
	}

	// TODO: check that the lookup succeeded
	BuiltinType fntype = typeLookup(currentToken->strData);

	// get the function name
	getNextToken();
	if(currentToken == NULL) return NULL;

	if(currentToken->getType() != Token::SYMBOL) {
		error(currentToken, "Expected valid function name for extern declaration, got ");
		return NULL;
	}

	std::string name(currentToken->strData);

	std::vector<ArgPair> arguments;

	getNextToken();
	// TODO: Allow newlines in function definitions
	// ensure this is a arglist starting token
	if(currentToken==NULL) return NULL;
	if(currentToken->getType() != Token::ARG_LIST_CONTAINER) {
		error(currentToken, "Expected argument list starting token ('|'), got ");
		return NULL;
	}

	bool foundEnd = false;
	getNextToken();
	while(currentToken != NULL) {
		if(currentToken->getType() == Token::TYPE_NAME) {
			// get the type 
			BuiltinType t = typeLookup(currentToken->strData);

			// now it needs to be a symbol
			getNextToken();
			if(currentToken == NULL) return NULL;

			if(currentToken->getType() != Token::SYMBOL) {
				error(currentToken, "Expected valid identifier, got ");
				return NULL;
			}

			std::string name = currentToken->strData;

			getNextToken();
			if(currentToken == NULL) return NULL;
			if(currentToken->getType() == Token::ARG_LIST_CONTAINER) {
				ArgPair pair(t, name);
				arguments.push_back(pair);
				foundEnd = true;
				break;
			} else if(currentToken->getType() == Token::SEPERATOR) {
				ArgPair pair(t, name);
				arguments.push_back(pair);
			}

		} else if(currentToken->getType() == Token::ARG_LIST_CONTAINER) {
			foundEnd = true;
			break;
		} else {
			error(currentToken, "Unexpected token in extern declaration argument list ");
			return NULL;
		}
	}

	if(!foundEnd) {
		error(currentToken, "Could not find end to extern declaration ");
		return NULL;
	} else getNextToken();

	return new FunctionDefinition(fntype, name, arguments);
}

FunctionBody *AbstractSyntaxTree::parseFunctionBody() {
	bool foundEnd = false;
	std::vector<Expression *> statements;

	while(currentToken != NULL && currentToken->getType() == Token::DELIMETER) getNextToken();
	
	if(currentToken == NULL) {
		std::cout << "Missing Function body" << std::endl;
		exit(-1);
	}


	if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END) {
		return new FunctionBody(statements);
	}

	while(!(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END)) {
		// keep looping until we get to an end token
		// we don't have to keep track of how many constructs are 
		// open and count the ends, because the internal parsing
		// functions will keep matching until an end as well, 
		// keeping everything together, unless an end is missing,
		// in which case the while above will fail and it can be detected

		Expression *exp = parseExpression();
		if(exp == NULL) {
			if(currentToken->getType() == Token::DELIMETER) {
				continue;
			} else if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END) {
				foundEnd = true;
				break;
			} else {
				error(currentToken, "Unexpected token");
				return NULL;
			}
		}

		statements.push_back(exp);

		// eat any delimiters
		while(currentToken != NULL && currentToken->getType() == Token::DELIMETER) 
			// re-assign currentToken here so the compiler doesn't
			// optomise out this loop
			currentToken = getNextToken();

		if(currentToken == NULL) {
			std::cout << "Missing function end" << std::endl;
			exit(-1);
		}

	}

	getNextToken(); // eat the 'end'
	return new FunctionBody(statements);
}

Expression *AbstractSyntaxTree::parsePrimaryExpression() {
	
	if(currentToken == NULL) return NULL;

	switch(currentToken->getType()) {
		
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
		// The '-' is both a unary and binary operator but it is not
		// defined as such to make the parsing simpler. That means
		// that the '-' operator could turn up here and so handle this
		// differently to the other operators.
		case Token::OPERATOR:
			if(operatorLookup(currentToken->strData) != MINUS) {
				error(currentToken, "Unexpected operator, expected unary operator or primary expression, got ");
				return NULL;
			}
			return parseUnaryOperation();
		break;

		case Token::DELIMETER:
			getNextToken();
			return NULL;
		break;
		case Token::KEYWORD:
		{
			Keyword k = keywordLookup(currentToken->strData);
			
			switch(k) {
				case END:
					return NULL;
				break;
				case IF:
					return parseIfStatement();
				break;
				case ELSE:
					return NULL;
				break;
				case WHILE:
					return parseWhileStatement();
				break;

				default:
					return NULL;
				break;
			}
		}
		break;

		default:
			error(currentToken, "Found unexpected token ");
			return NULL;
		break;
	}
}

Expression *AbstractSyntaxTree::parseExpression() {
	Expression *LHS = parseUnaryOperation();

	if(LHS == NULL) {
		if(currentToken->getType() == Token::DELIMETER) {
			getNextToken();
			return LHS;
		}
		return NULL;
	}

	if(currentToken->getType() == Token::SEPERATOR) {
		return LHS;
	}

	if(currentToken->getType() == Token::KEYWORD && keywordLookup(currentToken->strData) == END) {
		return LHS;
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
	while(currentToken->getType() != Token::CLOSE_PAREN) {
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
	// eat the close bracket
	// TODO: check it is a close bracket
	getNextToken();

	return new Call(name, args);	
}

Expression *AbstractSyntaxTree::parseBinaryOperationRHS(unsigned int minPrec, Expression *LHS) {

	// if it's a closing bracket return
	if(currentToken->getType() == Token::CLOSE_PAREN) return LHS;

	if(unaryOperatorLookup(currentToken->strData) != NOT_UNARY)
		return parseUnaryOperation();

	// if it is a binary operation find the precedence
	while(true) {

		if(currentToken->getType() == Token::DELIMETER) {
			//getNextToken(); // eat it
			return LHS;
		} 

		// TODO: ensure this gives something meaningful

		Operator op = operatorLookup(currentToken->strData);
		unsigned int prec = precedenceLookup(op);

		if(prec < minPrec) return LHS;

		getNextToken(); // eat operator

		Expression *RHS = parseUnaryOperation();
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
		} else if(currentToken->getType() == Token::CLOSE_PAREN) {
			// if the token is a close bracket, either the function call
			// or paranthesis expression code should handle it
			return new BinaryOperation(LHS, op, RHS);
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
		return new VariableInitialisation(t, name);
	}
}

Expression *AbstractSyntaxTree::parseIfStatement() {
	// TODO: Sanity check currentToken is definitely a if keyword
	Token *ifTok = currentToken;
	getNextToken();
	Expression *predicate = parseExpression();
	if(predicate == NULL) {
		// either an end or an else keyword
		Keyword k = keywordLookup(currentToken->strData);
		if(k == END) {
			//empty if, can ignore
			#if defined(DEBUG)
				std::cout << "Ignoring empty if statement: [" << currentToken->filename << ":" << currentToken->line << "]\n";
			#endif
		} else if(k == ELSE) {
			std::cout << "Not implemented error: else in " <<__FILE__ << ":" << __LINE__ << std::endl;
		}
	}

	std::vector<Expression *> statements;
	std::vector<Expression *> elseStatements;

	std::vector<Expression *> *currentList = &statements;
	bool foundEnd = false, foundElse = false;
	while(currentToken != NULL) {
		// std::cout << "Current token type: " << currentToken->getType() << "\n";
		if(currentToken->getType() == Token::DELIMETER) {
			getNextToken();
			continue;
		}

		if(currentToken->getType() == Token::KEYWORD) {
			Keyword k = keywordLookup(currentToken->strData);
			if(k == END) {
				getNextToken();
				foundEnd = true;
				break;
			} else if(k == ELSE) {
				if(foundElse) {
					error(currentToken, "Found second else parameter");
					return NULL;
				}
				foundElse = true;

				// start saving the statements to the else list now
				currentList = &elseStatements;
				getNextToken();
				continue;
			}
		}

		Expression *st = parseExpression();
		if(st == NULL) return NULL;
		currentList->push_back(st);

	}

	if(!foundEnd) {
		error(ifTok, "Did not find end to if statement");
		return NULL;
	}

	if(elseStatements.size() == 0) {
		return new IfStatement(predicate, statements);
	} else {
		return new IfStatement(predicate, statements, elseStatements);
	}
}

Expression *AbstractSyntaxTree::parseWhileStatement() {
	// TODO: Check it's a while token
	Token *whileTok = currentToken;
	getNextToken();

	Expression *predicate = parseExpression();
	if(predicate == NULL){
		std::cout << "NULL from here " << __FILE__ << ":" << __LINE__ << std::endl;
		return NULL;
	}

	std::vector<Expression *> statements;
	bool foundEnd = false;
	while(currentToken != NULL) {
		if(currentToken->getType() == Token::DELIMETER){
			getNextToken();
			continue;
		}

		if(currentToken->getType() == Token::KEYWORD) {
			Keyword k = keywordLookup(currentToken->strData);

			if(k == END) {
				foundEnd = true;
				getNextToken();
				break;
			} 
			
		}

		Expression *e = parseExpression();
		if(e == NULL) return NULL;
		statements.push_back(e);
	}

	if(!foundEnd) {
		error(whileTok, "Did not find end to while statement");
		return NULL;
	}

	return new WhileStatement(predicate, statements);
}

Expression *AbstractSyntaxTree::parseUnaryOperation() {
	UnaryOperator op;
	if((op = unaryOperatorLookup(currentToken->strData)) == NOT_UNARY){
		// must be a primary expression or a unary minus masquerading
		// as a binary operator
		if(operatorLookup(currentToken->strData) == MINUS) {
			// TODO: More stringent checking that we don't have 
			// a syntax error
			op = UNARYMINUS;
			goto makeUnaryOperation;
		} else return parsePrimaryExpression();
	}

	makeUnaryOperation:
	getNextToken();
	if(Expression *operand = parseUnaryOperation())
		return new UnaryOperation(op, operand);
	return NULL;

}


void AbstractSyntaxTree::error(Token *t, std::string message) {
	std::cout << "Error: " << message << " `" << t->strData
			<< "'"
#if defined(DEBUG)
			<< " of type " << t->getType()
#endif
			<< " [" << t->filename << ":"
			<< t->line << "]" << std::endl;
#if defined(DEBUG)
	showLast3Tokens();
	
#endif
}

#if defined(DEBUG)
void AbstractSyntaxTree::showLast3Tokens() {
	int i = 1;
	std::vector<Token> lastTokens;
	while(i <= 3 && tokenIdx - i >= 0) {
		lastTokens.push_back(tokens[tokenIdx - i]);
		++i;
	}

	std::cout << "Last 3 tokens in reverse order:" << std::endl;
	
	for(int i = 0; i < lastTokens.size(); ++i){
		Token t = lastTokens[i];
		std::cout << "\t" << t.getType() << " : " << t.strData << std::endl;
	}
}
#endif