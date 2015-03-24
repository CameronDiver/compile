#ifndef AST_CALL_H
#define AST_CALL_H

#include <string>
#include <vector>


#include "expression.h"

class Call : public Expression {
public:
	std::string symbol;
	std::vector<Expression *> args;

	Call(std::string fname, std::vector<Expression *> fargs) : symbol(fname), args(fargs){}

};

#endif // AST_CALL_H
