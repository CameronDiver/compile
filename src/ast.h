#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

#include "token.h"
#include "builtins.h"

#include "ast/expression.h"
#include "ast/intliteral.h"
#include "ast/symbolref.h"
#include "ast/floatliteral.h"
#include "ast/call.h"
#include "ast/binaryoperation.h"
#include "ast/functiondef.h"
#include "ast/functionbody.h"
#include "ast/variableinit.h"

// the current function
extern FunctionDefinition *currentFn;

class AbstractSyntaxTree {
public:
	std::vector<FunctionDefinition *> functions;
	AbstractSyntaxTree(std::vector<Token> &tokens);

private:
	int tokenIdx;
	Token *currentToken;
	std::vector<Token> tokens;

	// Increment the token index and return the new token
	Token *getNextToken();

	// Look at the next token without increasing the token index
	Token *peekNextToken();

	// For the time being the only thing that can appear in the root
	// of the programs are function definitions
	FunctionDefinition 	*parseTopLevel();
	FunctionBody 		*parseFunctionBody();


	Expression 			*parseExpression();
	Expression 			*parsePrimaryExpression();

	// attempt to parse the expression as a binary operation, returning the single
	// expression if not
	Expression 			*parseBinaryOperationRHS(unsigned int minPrec, Expression *LHS);

	Expression 			*parseVariableDeclaration();
	Expression 			*parseIntegerLiteral();
	Expression 			*parseFloatLiteral();
	Expression 			*parseParenExpression();
	Expression 			*parseIdentifierReference();
	Expression 			*parseFunctionCall();



	void error(Token *t, std::string message);

	// functions good for debugging
#if defined(DEBUG)
	// print the last 3 tokens of the stack, in reverse order,
	// as if being popped off
	void showLast3Tokens();
#endif

};

#endif // AST_H
