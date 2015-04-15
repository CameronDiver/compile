#include "binaryoperation.h"


#include <iostream>
#include <cstdlib>

#include "codegen.h"

bool BinaryOperation::isAssigmentOperation() {
	switch(op) {
		case EQUALS:
		case PLUSEQ:
		case MINUSEQ:
		case MULTEQ:
		case DIVEQ:
			return true;
		default:
			return false;
	}
}

llvm::Value *BinaryOperation::assigmentCodegen() {
	// make sure that the lvalue is a symbol
	SymbolReference *s = dynamic_cast<SymbolReference *>(LHS);

	if(s == NULL) {
		std::cout << "Error: invalid lvalue" << std::endl;
		exit(-1);
	}
	switch(op){
		case EQUALS:
		{
			// true argument because we want the address not value
			llvm::Value *L = s->codegen(true);
			llvm::Value *R = RHS->codegen();

			if(!L || !R) {
				std::cout << "Null LLVM value from binary operation [" << __FILE__<< ":" << __LINE__ <<"]\n";
				exit(-1);
			}

			return Builder.CreateStore(R, L);
		}
		break;
		case PLUSEQ:
			// make these operations reduce to an equals
			return (new BinaryOperation(s, EQUALS, new BinaryOperation(s, PLUS, RHS)))->codegen();
		break;
		case MINUSEQ:
			return (new BinaryOperation(s, EQUALS, new BinaryOperation(s, MINUS, RHS)))->codegen();
		break;
		case MULTEQ:
			return (new BinaryOperation(s, EQUALS, new BinaryOperation(s, MULT, RHS)))->codegen();
		break;
		case DIVEQ:
			return (new BinaryOperation(s, EQUALS, new BinaryOperation(s, DIV, RHS)))->codegen();
		break;

		default:
			std::cout << "Inconsistent compiler state [" << __FILE__ << ":" << __LINE__ << "]" <<  std::endl;
			exit(-1);
		break;
	}
}

llvm::Value *BinaryOperation::codegen() {

	// do a switch here to check if it is an assigment operation,
	// which needs to be handled differently
	if(isAssigmentOperation()) {
		return assigmentCodegen();
	}
	/*if(op == EQUALS) {
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
	}*/


	llvm::Value *L = LHS->codegen();
	llvm::Value *R = RHS->codegen();
	if(L == NULL | R == NULL) {
		std::cout << "Null LLVM value from binary operation" << std::endl;
		exit(-1);
	}

	switch(op) {
		case PLUS:
			return Builder.CreateAdd(L, R, "addtmp");
		break;
		case MINUS:
			return Builder.CreateSub(L, R, "subtmp");
		break;
		case MULT:
			return Builder.CreateMul(L, R, "multmp");
		break;
		case DIV:

		break;
		
		case LESSTHAN:
			return Builder.CreateICmpULT(L, R, "lttmp");
		break;

		case GREATTHAN:
			return Builder.CreateICmpUGT(L, R, "greatthantmp");
		break;

		case NOTEQUALS:
			return Builder.CreateICmpNE(L, R, "neqtmp");
		break;

		case LESSTHANEQ:
			return Builder.CreateICmpULE(L, R, "ltetmp");
		break;
		case GREATTHANEQ:
			return Builder.CreateICmpUGE(L, R, "gtetmp");
		break;
		case COMPARISON:
			return Builder.CreateICmpEQ(L, R, "comptmp");
		break;




		case NOT_OP:
			std::cout << "Invalid binary operator" << std::endl;
			exit(-1);
		break;
		default:
			std::cout << "Currently unsupported operator: " << op << std::endl;
			exit(-1);
		break;
	}

}