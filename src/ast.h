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
#include "ast/variabledec.h"

class AbstractSyntaxTree {
public:
	AbstractSyntaxTree(std::vector<Token> &tokens);

private:
	int tokenIdx = 0;
	Token *currentToken;
	std::vector<Token> tokens;
	std::vector<FunctionDefinition *> functions;

	// Increment the token index and return the new token
	Token *getNextToken();

	// Look at the next token without increasing the token index
	Token *peekNextToken();

	// For the time being the only thing that can appear in the root
	// of the programs are function definitions
	FunctionDefinition 	*parseTopLevel();
	FunctionBody 		*parseFunctionBody();



	void error(Token *t, std::string message);
};

#endif // AST_H
