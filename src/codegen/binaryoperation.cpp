#include "binaryoperation.h"


#include <iostream>
#include <cstdlib>

llvm::Value *BinaryOperation::codegen() {
	llvm::Value *L = LHS->codegen();
	llvm::Value *R = RHS->codegen();
	if(L == NULL | R == NULL) {
		std::cout << "Null LLVM value from binary operation" << std::endl;
		exit(-1);
	}

	switch(op) {
		case PLUS:
			if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
				std::cout << "Only integer addition supported" << std::endl;
				exit(-1);
			}
			return Builder.CreateAdd(L, R, "addtmp");
		break;
		case MINUS:
			if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
				std::cout << "Only integer subtraction supported" << std::endl;
				exit(-1);
			}
			return Builder.CreateSub(L, R, "subtmp");
		break;
		case MULT:
			if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
				std::cout << "Only integer multiplication supported" << std::endl;
				exit(-1);
			}
			return Builder.CreateMul(L, R, "multmp");
		break;
		// case DIV:
		// break;

		// case EQUALS:
		// break;


		case NOT_OP:
		default:
			std::cout << "Invalid binary operator" << std::endl;
			exit(-1);
		break;
	}

}