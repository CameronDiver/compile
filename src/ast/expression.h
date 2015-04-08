#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <string>
#include "builtins.h"

class Expression {
public:
	virtual ~Expression() {};

	virtual llvm::Value *codegen() = 0;

#if defined(DEBUG)
	virtual std::string prettyPrint() = 0;
#endif
};

#endif // AST_EXPRESSION_H
