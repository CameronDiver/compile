#ifndef AST_FLOAT_LITERAL_H
#define AST_FLOAT_LITERAL_H

#include "expression.h"

class FloatLiteral : public Expression {
public:
	float value;
	FloatLiteral(float val) : value(val){}


#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Float Literal: " << value;
		return ss.str();
	}
#endif
};


#endif // AST_FLOAT_LITERAL_H
