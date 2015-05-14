#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <string>
#include "builtins.h"

class Expression {
public:
	virtual ~Expression() {};

	virtual llvm::Value *codegen() = 0;

	virtual bool isLiteral() {
		// the literal classes override this function
		return false;
	}

#if defined(DEBUG)
	virtual std::string prettyPrint() = 0;
#endif
};

#endif // AST_EXPRESSION_H
