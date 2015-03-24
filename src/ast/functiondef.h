#ifndef AST_FUNCTION_DEFINITION_H
#define AST_FUNCTION_DEFINITION_H

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "../builtins.h"
#include "expression.h"
#include "functionbody.h"

typedef std::vector<std::pair<BuiltinType, std::string>> ArgPair;

class FunctionDefintion { // TODO: extend something like 'RootStatement'
public:
	BuiltinType type;
	std::string fname;
	ArgPair arguments;

	FunctionBody *body;

	FunctionDefintion(BuiltinType t, std::string symbolName, ArgPair args, FunctionBody *fbody)
		: type(t), fname(symbolName), arguments(args), body(fbody) {}

#if defined(DEBUG)
	std::string prettyPrint() {
		stringstream ss;
		ss << "Function definition: Type:" << type << ", "  << fname << " [" << arguments.size() << " args]";
		return ss.str(); 
	}
#endif 

};

#endif // AST_FUNCTION_DEFINITION_H
