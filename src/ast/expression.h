#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <string>

class Expression {
public:
	virtual ~Expression() {};

#if defined(DEBUG)
	virtual std::string prettyPrint() = 0;
#endif
};

#endif // AST_EXPRESSION_H
