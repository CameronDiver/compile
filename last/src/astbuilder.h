#ifndef AST_BUILDER_H
#define AST_BUILDER_H

#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cstdint>

#include "ast/expression.h"
#include "ast/intexpression.h"
#include "ast/varexpression.h"
#include "ast/callexpression.h"
#include "ast/functionexpression.h"
#include "ast/binaryexpression.h"

#include "token.h"
#include "types.h"

class ASTBuilder {
public:
	ASTBuilder(std::vector<Token> &tokens);

	// Define the different types of token it can be
	enum {
		INTEGER,
		SYMBOL,
		CALL,
		PROTO,
		FUNCTION
	};

private:
	unsigned int tokenIdx;
	std::vector<Token> *tokens;
	
	// create the AST
	void parse();

	Expression *parseTopLevelStatement();


	Expression *parseIntegerExpression();
	Expression *parseParensExpression();
	Expression *parseIdentifierExpression();
	Expression *parseExpression();

	Expression *parseFunctionDefinition();


	// TODO: Move these out of this class if necessary
	inline static bool isInteger(const std::string &data) {
		return std::all_of(data.begin(), data.end(), static_cast<int(*)(int)>(std::isdigit));
	}

	inline static bool isSymbol(const std::string &data) {
		// FIXME: Change this code to accept more things for symbols, not just alpha chars
		return std::all_of(data.begin(), data.end(), static_cast<int(*)(int)>(std::isalpha));
	}

	// get the next token and advance the token index
	inline Token *getNextToken() {
		if(tokenIdx >= tokens->size()) return NULL;

		Token *ret = &tokens->at(tokenIdx);
		++tokenIdx;
		return ret;
	}

	inline Token *getCurrentToken() {
		if(tokenIdx >= tokens->size()) return NULL;

		return &tokens->at(tokenIdx);
	}

	// Get the next token, but don't increase the token idx
	inline Token *peekNextToken() {
		if((tokenIdx + 1) >= tokens->size()) return NULL;

		return &tokens->at(tokenIdx + 1);
	}

	// TODO: Make this code more extendable and nicer
	inline bool isBuiltinTypeName(const std::string &data) {
		if(!data.compare("void"))
			return true;
		if(!data.compare("int"))
			return true;
		if(!data.compare("string"))
			return true;
		return false;
	}

	inline int32_t static stringToInteger(const std::string &data) {
		stringstream ss(data);
		
		int32_t ret;
		// TODO: checking
		ss >> ret;

		return ret;
	}


	// the 'root node' of the tree
	std::vector<Expression *> tree;
};


#endif // AST_BUILDER_H
