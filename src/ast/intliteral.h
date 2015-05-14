#ifndef AST_INT_LITERAL_H
#define AST_INT_LITERAL_H

#include <string>
#include <sstream>
#include <cstdint>

#include "expression.h"

#include "types/types.h"

class IntLiteral : public Expression {
public:
	enum Subtypes {
		SIGNED,
		LONG
	};

	int64_t value;
	LanguageType *type;


	IntLiteral(int64_t val) : value(val) {}

	llvm::Value *codegen();


	bool isLiteral() { return true; }

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Integer Literal: " << value;
		return ss.str();
	}
#endif
};


#endif // AST_INT_LITERAL_H
