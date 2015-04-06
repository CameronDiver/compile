#ifndef AST_VARIABLE_DECLARATION_H
#define AST_VARIABLE_DECLARATION_H

#include <string>
#include <sstream>

#include "../builtins.h"
#include "expression.h"

class VariableDeclaration : public Expression {
public:
	BuiltinType type;
	std::string symbol;

	Expression *RHS;

	VariableDeclaration(BuiltinType _type, std::string name)
	: type(_type), symbol(name) {RHS = NULL;}
	VariableDeclaration(BuiltinType _type, std::string name, Expression *rhs)
	: type(_type), symbol(name), RHS(rhs) {}

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Variable Declaration: Type " << type << ", " << symbol;

		if(RHS != NULL) {
			ss << '=' << RHS->prettyPrint();
		}

		return ss.str();
	}
#endif
};

#endif // AST_VARIABLE_DECLARATION_H
