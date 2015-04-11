#include "jit.h"


#include <iostream>
#include <vector>
using namespace llvm;

JITExecution::JITExecution() {
	LLVMInitializeNativeTarget();
	// create the execution engine and register the module with it
	//executionEngine = EngineBuilder(module).create();
	executionEngine = ExecutionEngine::create(module, false);
}

int JITExecution::callMain() {
	std::vector<GenericValue> noargs;
	Function *fn = executionEngine->FindFunctionNamed("main");
	if(fn == NULL) {
		std::cout << "Couldn't find function main" << std::endl;
		return -1;
	}

	GenericValue g = executionEngine->runFunction(fn, noargs);
	
	int a = ~0;
	return g.IntVal.getLimitedValue(a);
}