#ifndef AST_FUNCTION_BODY_H
#define AST_FUNCTION_BODY_H

#include <string>
#include <sstream>
#include <vector>

#include "../builtins.h"
#include "expression.h"

class FunctionBody {
public:

	std::map<std::string, llvm::AllocaInst *> stackVariables;
	std::map<std::string, llvm::Value *> argVariables;

	std::vector<Expression *> statements;

	FunctionBody(std::vector<Expression *> stmts): statements(stmts) {}

	llvm::Value *codegen();
	
#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Function Body:" << std::endl;
		for(int x = 0; x < statements.size(); ++x) {
			ss << "  " << statements[x]->prettyPrint() << std::endl;
		}
		return ss.str();
	}
#endif
};

#endif // AST_FUNCTION_BODY_H
