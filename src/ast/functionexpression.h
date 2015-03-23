#ifndef AST_FUNCTION_EXPRESSION_H
#define AST_FUNCTION_EXPRESSION_H

#include "expression.h"
#include "prototypeexpression.h"

class FunctionExpression : public Expression {
	PrototypeExpression *proto;
	Expression *body;

public:
	FunctionExpression(PrototypeExpression * _proto, Expression *_body)
		: proto(_proto), body(_body) {}
};


#endif // AST_FUNCTION_EXPRESSION_H
