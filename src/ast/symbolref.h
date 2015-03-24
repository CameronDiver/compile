#ifndef AST_SYMBOL_REF_H
#define AST_SYMBOL_REF_H

#include "expression.h"


class SymbolReference : public Expression {
public:
	std::string name;

	Symbol(std::string data) : name(data) {};
};

#endif // AST_SYMBOL_REF_H
