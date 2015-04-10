#include "call.h"

#include <iostream>
#include <vector>
#include <sstream>

llvm::Value *Call::codegen() {
	llvm::Function *fn = Module->getFunction(symbol);
	if(fn == NULL) {
		std::cout << "Invalid function " << symbol << std::endl;
		exit(-1);
	}
	

	// check that the arguments are the same size
	if(fn->arg_size() != args.size()) {
		std::cout << "Argument size mismatch for call to function " << symbol << std::endl;
		exit(-1);
	}

	std::vector<llvm::Value *> argValues;
	for(unsigned i = 0; i < args.size(); ++i) {
		llvm::Value *val = args[i]->codegen();
		if(val == NULL) {
			std::cout << "Bad value " << __FILE__ <<":"<< __LINE__ << std::endl;
			exit(-1);
		}

		argValues.push_back(val);
	}

	std::stringstream name("");
	name << "call_"<< symbol << "_tmp"; 
	return Builder.CreateCall(fn, argValues, name.str());
}