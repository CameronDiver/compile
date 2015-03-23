#ifndef AST_VAR_EXPRESSION_H
#define AST_VAR_EXPRESSION_H

#include <string>

#include "expression.h"

// AST node class for referencing a variable
class VarExpression : public Expression {
	std::string symbol;

public:
	VarExpression(const std::string &name) : symbol(name) {}
	
};


#endif // AST_VAR_EXPRESSION_H
