#ifndef AST_INT_LITERAL_H
#define AST_INT_LITERAL_H

#include <string>
#include <sstream>
#include <cstdint>

#include "expression.h"

class IntLiteral : public Expression {
public:
	uint32_t value;
	IntLiteral(uint32_t val) : value(val) {}

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Integer Literal: " << value;
		return ss.str();
	}
#endif
};


#endif // AST_INT_LITERAL_H
