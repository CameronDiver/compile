#ifndef AST_FLOAT_LITERAL_H
#define AST_FLOAT_LITERAL_H

#include "expression.h"
#include "types/languagetype.h"
#include <sstream>

class FloatLiteral : public Expression {
public:
	float value;
	FloatLiteral(float val) : value(val){}

	llvm::Value *codegen();

	LanguageType *type;

	bool isLiteral() { return true; }

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss("Float Literal: ");
		ss << value;
		return ss.str();
	}
#endif
};


#endif // AST_FLOAT_LITERAL_H
