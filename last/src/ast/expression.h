#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <string>

// Base class for all expression nodes in the abstract
// syntax tree
class Expression {
public:
	virtual ~Expression(){};

	virtual std::string getStrRep() = 0;

};

#endif /* AST_EXPRESSION_H */