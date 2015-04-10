#include "variableinit.h"

#include "codegen.h"
using namespace llvm;

Value *VariableInitialisation::codegen() {
	Value *init = NULL;
	if(RHS != NULL) {
		
		init = RHS->codegen();
		
	} else {
		
		init = CodeGen::getInitialiser(type);
		
	}
	
	Function *fn = Builder.GetInsertBlock()->getParent();
	
	AllocaInst *allocation = CodeGen::createEntryBlockAlloca(fn, name, type);
	
	Builder.CreateStore(init, allocation);
	

	currentFn->body->stackVariables[name] = allocation;
	return init;
}