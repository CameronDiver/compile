#ifndef AST_FUNCTION_DEFINITION_H
#define AST_FUNCTION_DEFINITION_H

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "../builtins.h"
#include "expression.h"
#include "functionbody.h"

typedef std::pair<BuiltinType, std::string> ArgPair;

class FunctionDefinition { // TODO: extend something like 'RootStatement'
public:
	BuiltinType type;
	std::string fname;
	std::vector<ArgPair> arguments;

	FunctionBody *body;

	FunctionDefinition(BuiltinType t, std::string symbolName, std::vector<ArgPair> args, FunctionBody *fbody)
		: type(t), fname(symbolName), arguments(args), body(fbody) { prettyPrint(); }

	llvm::Function *codegen();
	void allocateArgVars(llvm::Function *fn);

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss;
		ss << "Function definition: Type:" << type << ", "  << fname << " [" << arguments.size() << " args]";
		ss << body->prettyPrint();
		return ss.str(); 
	}
#endif 

};

#endif // AST_FUNCTION_DEFINITION_H
