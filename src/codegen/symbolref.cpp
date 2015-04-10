#include "symbolref.h"

#include <iostream>
#include "codegen.h"
using namespace llvm;

// FIXME: This function assumes we are already in a function
Value *SymbolReference::codegen() {
	FunctionDefinition *fn = currentFn;

	Value *v;

	v = fn->body->stackVariables[name];
	if(v == NULL) {
		// check to see if it's a function variable
		v = fn->body->argVariables[name];
		if(v == NULL) {
			std::cout << "Error: Undefined identifier " << name << std::endl;
			exit(-1);
		}
	}
	return v;
}