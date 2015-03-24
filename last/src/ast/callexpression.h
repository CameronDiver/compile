#ifndef AST_CALL_EXPRESSION_H
#define AST_CALL_EXPRESSION_H

#include <string>
#include <vector>

#include "expression.h"

class CallExpression : public Expression {
	std::string callee;
	std::vector<Expression *> args;

public:
	CallExpression(const std::string &_callee, std::vector<Expression *> &_args)
		: callee(_callee), args(_args) {}

	std::string getStrRep() {
		return callee;
	}
};


#endif // AST_CALL_EXPRESSION_H
