#ifndef AST_INT_EXPRESSION_H
#define AST_INT_EXPRESSION_H

#include <cstdint>
#include <sstream>

#include "expression.h"

class IntExpression : public Expression {
	int32_t value;

public:
	IntExpression(int32_t val) : value(val) {}

	std::string getStrRep() {
		std::stringstream ss("");

		ss << value;

		return ss.str();
	}
};

#endif /* AST_INT_EXPRESSION_H */