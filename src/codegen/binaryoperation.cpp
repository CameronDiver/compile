#include "binaryoperation.h"


#include <iostream>
#include <cstdlib>

#include "codegen.h"

llvm::Value *BinaryOperation::codegen() {

	if(op == EQUALS) {
		// check that the LHS is definitely a symbol
		SymbolReference *s = dynamic_cast<SymbolReference *>(LHS);
		if(s == NULL) {
			std::cout << "only symbols can be on left hand side of =" << std::endl;
		}

		// need the address here
		llvm::Value *L = s->codegen(true);
		llvm::Value *R = RHS->codegen();
		if(!L || !R) {
			std::cout << "Null LLVM value from binary operation" << std::endl;
			exit(-1);
		}

		return Builder.CreateStore(R, L);
	}


	llvm::Value *L = LHS->codegen();
	llvm::Value *R = RHS->codegen();
	if(L == NULL | R == NULL) {
		std::cout << "Null LLVM value from binary operation" << std::endl;
		exit(-1);
	}

	switch(op) {
		case PLUS:
			//L->dump();
			/*if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
				std::cout << "Only integer addition supported" << std::endl;
				exit(-1);
			}*/
			return Builder.CreateAdd(L, R, "addtmp");
		break;
		case MINUS:
			// if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
			// 	std::cout << "Only integer subtraction supported" << std::endl;
			// 	exit(-1);
			// }
			return Builder.CreateSub(L, R, "subtmp");
		break;
		case MULT:
			// if(!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy()) {
			// 	std::cout << "Only integer multiplication supported" << std::endl;
			// 	exit(-1);
			// }
			return Builder.CreateMul(L, R, "multmp");
		break;
		// case DIV:
		// break;


		case NOT_OP:
		default:
			std::cout << "Invalid binary operator" << std::endl;
			exit(-1);
		break;
	}

}