#ifndef AST_SYMBOL_REF_H
#define AST_SYMBOL_REF_H

#include <sstream>

#include "expression.h"


class SymbolReference : public Expression {
public:
	std::string name;

	SymbolReference(std::string data) : name(data) {};

	llvm::Value *codegen(bool address);
	llvm::Value *codegen();

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Symbol Reference: " << name;
		return ss.str();
	}
#endif
};

#endif // AST_SYMBOL_REF_H
