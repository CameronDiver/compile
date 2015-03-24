#ifndef AST_INT_LITERAL_H
#define AST_INT_LITERAL_H

#include "expression.h"

class IntLiteral : public Expression {
public:
	uint32_t value;
	IntLiteral(uint32_t val) : value(val) {}
};


#endif // AST_INT_LITERAL_H
