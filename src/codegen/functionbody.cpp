#include "functionbody.h"

#include <cstdlib>
#include <iostream>
using namespace llvm;


Value *FunctionBody::codegen() {
	// go through all of the statements and generate code for the function
	llvm::Value *last = NULL;
	for(unsigned int i = 0; i < statements.size(); ++i) {
		if(statements[i] == NULL) {
			// FIXME: empty function or error?
		} else {
			Value *val = statements[i]->codegen();

			/*if(val == NULL) {
				std::cout << "An error occured" << std::endl;
				exit(-1);
			}*/
			last = val;
		}
	}
	return last;
}