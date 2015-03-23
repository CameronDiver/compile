#ifndef AST_PROTOTYPE_EXPRESSION_H
#define AST_PROTOTYPE_EXPRESSION_H

#include <vector>
#include <string>

#include "expression.h"

class PrototypeExpression : public Expression {
	std::string symbol;
	std::vector<std::string> args;

public:
	PrototypeExpression(std::string name, std::vector<std::string> _args)
		: symbol(name), args(_args) {}
};

#endif // AST_PROTOTYPE_EXPRESSION_H
