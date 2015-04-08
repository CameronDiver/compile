#include "functiondef.h"

#include <iostream>
#include "codegen.h"

llvm::Function *FunctionDefinition::codegen() {
	// organise the arguments into their types
	std::vector<llvm::Type *> argumentTypes;
	for(unsigned i = 0; i < arguments.size(); ++i) {
		ArgPair arg = arguments[i];
		argumentTypes.push_back(CodeGen::getTypeFromBuiltin(arg.first));
		// TODO: check type return isn't NULL
	}

	// false means not vararg
	// TODO: Also check return isn't NULL here
	llvm::FunctionType *fnType = llvm::FunctionType::get(CodeGen::getTypeFromBuiltin(type), argumentTypes, false);

	llvm::Function *fn = 
	llvm::Function::Create(fnType, 
		llvm::Function::ExternalLinkage, fname, Module);

	// check that there isn't already a function with the same name
	if(fn->getName() != fname) {
		fn->eraseFromParent();
		fn = Module->getFunction(fname);

		// check if the function has a body, if so
		// this is a redclecaration
		if(!fn->empty()){
			std::cout<<"Error function redeclaration"<<std::endl;
			exit(-1);
		}

		if(fn->arg_size() != arguments.size()) {
			std::cout<<"Error function redeclaration with differing argument counts"<<std::endl;
			exit(-1);
		}

	}

	// set all the argument names
	unsigned idx = 0;
	for(llvm::Function::arg_iterator i = fn->arg_begin();
		idx != arguments.size(); ++i, ++idx) {
		i->setName(arguments[idx].second);

		CodeGen::Symbols[arguments[idx].second] = i;
	}

	// create a new basic block for entering the function
	llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", fn);
	Builder.SetInsertPoint(basicBlock);

	if(llvm::Value *ret = body->codegen()) {
		Builder.CreateRet(ret);

		llvm::verifyFunction(*fn);

		return fn;
	}
	// error
	fn->eraseFromParent();
	return NULL;
}