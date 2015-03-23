#ifndef AST_BINARY_EXPRESSION_H
#define AST_BINARY_EXPRESSION_H

#include "expression.h"

class BinaryExpression : public Expression {
	// FIXME: This doesn't allow for double byte
	// operators or things like that, use a better
	// way  of defining what kind of operator it is
	char opChar;
	// The expressions of the binary operation
	Expression *LHS, *RHS;

public:
	BinaryExpression(char op, Expression *lhs, Expression *rhs)
		: opChar(op), LHS(lhs), RHS(rhs) {}
};

#endif // AST_BINARY_EXPRESSION_H
