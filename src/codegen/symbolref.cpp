#include "symbolref.h"

#include <iostream>
#include "codegen.h"
using namespace llvm;

// FIXME: This function assumes we are already in a function
// TODO: need to know whether we need the address or the value
// for either assigning or referencing
Value *SymbolReference::codegen(bool address=false) {
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
	if(address)
		return v;
	
	return Builder.CreateLoad(v, name);
}

Value *SymbolReference::codegen() {
	return codegen(false);
}