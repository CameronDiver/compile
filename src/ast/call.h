#ifndef AST_CALL_H
#define AST_CALL_H

#include <string>
#include <vector>
#include <sstream>


#include "expression.h"

class Call : public Expression {
public:
	std::string symbol;
	std::vector<Expression *> args;

	Call(std::string fname, std::vector<Expression *> fargs) : symbol(fname), args(fargs){}

	llvm::Value *codegen();

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Function call: " << symbol << "(";
		bool fst = true;
		for(int x = 0; x < args.size(); ++x) {
			if(fst){
				ss << args[x]->prettyPrint();
				fst = false;
			} else 
				ss << ", " << args[x]->prettyPrint();
		}

		ss << ")";
		return ss.str();
	}
#endif

};

#endif // AST_CALL_H
