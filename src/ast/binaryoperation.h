#ifndef AST_BINARY_OPERATION_H
#define AST_BINARY_OPERATION_H


#include <string>
#include <sstream>

#include "expression.h"
#include "builtins.h"

class BinaryOperation : public Expression {
public:
	Expression *LHS;
	Expression *RHS;
	Operator op;

	BinaryOperation(Expression *lhs, Operator _op, Expression *rhs) : LHS(lhs), op(_op), RHS(rhs) {}


	// TODO: make a static helper function which grabs the Operator enum value from the string of the operator
};


#endif // AST_BINARY_OPERATION_H
