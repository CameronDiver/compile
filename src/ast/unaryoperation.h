#ifndef AST_UNARY_OPERATION_H
#define AST_UNARY_OPERATION_H

#include "expression.h"
#include <sstream>

class UnaryOperation : public Expression {
public:
	UnaryOperator op;
	Expression *operand;
	UnaryOperation(UnaryOperator _op, Expression *_operand)
	: op(_op), operand(_operand) {};

	llvm::Value *codegen();

#if defined(DEBUG)
	// TODO: stringFromUnaryOperator. Probably not in this class
	std::string prettyPrint() {
		std::stringstream ss("Unary Operation: ");
		ss << op << "(TODO: string from unaryOperator)" << operand->prettyPrint() << "\n"; 
		return ss.str();
	}
#endif
};

#endif /* AST_UNARY_OPERATION_H */