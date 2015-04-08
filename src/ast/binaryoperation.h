#ifndef AST_BINARY_OPERATION_H
#define AST_BINARY_OPERATION_H


#include <string>
#include <sstream>

#include "expression.h"
#include "../builtins.h"

class BinaryOperation : public Expression {
public:
	Expression *LHS;
	Expression *RHS;
	Operator op;

	BinaryOperation(Expression *lhs, Operator _op, Expression *rhs) : LHS(lhs), RHS(rhs), op(_op) {}

	llvm::Value *codegen();

	// TODO: make a static helper function which grabs the Operator enum value from the string of the operator

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Binary Operation: " << LHS->prettyPrint() << op << RHS->prettyPrint();
		return ss.str();
	}
#endif
};


#endif // AST_BINARY_OPERATION_H
