#ifndef AST_PROTOTYPE_EXPRESSION_H
#define AST_PROTOTYPE_EXPRESSION_H

#include <vector>
#include <string>
#include <sstream>

#include "expression.h"

class PrototypeExpression : public Expression {
	std::string symbol;
	std::vector<std::string> args;

public:
	PrototypeExpression(std::string name, std::vector<std::string> _args)
		: symbol(name), args(_args) {}

	std::string getStrRep() {
		std::stringstream ss;
		ss << "Function declaration: " << symbol << "(";
		bool fst = true;
		for(int x = 0; x < args.size(); ++x) {
			if(fst){
				ss << args[x];
				fst = false;
			}
			else
				ss << ", " <<  args[x];
		}
		ss << ")";
		return ss.str();
	}
};

#endif // AST_PROTOTYPE_EXPRESSION_H
