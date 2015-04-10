#ifndef AST_VARIABLE_INIT_H
#define AST_VARIABLE_INIT_H

#include <string>
#include <sstream>

#include "expression.h"

class VariableInitialisation : public Expression {
public:
	BuiltinType type;
	std::string name;
	Expression *RHS;

	VariableInitialisation(BuiltinType t, std::string _name, Expression *rhs)
	: type(t), name(_name), RHS(rhs) {}
	VariableInitialisation(BuiltinType t, std::string _name)
	: type(t), name(_name), RHS(NULL) {}

	llvm::Value *codegen();

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << type << " " << name << " = " << RHS->prettyPrint();
		return ss.str(); 
	}
#endif
};

#endif // AST_VARIABLE_INIT_H
