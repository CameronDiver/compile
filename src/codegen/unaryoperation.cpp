#include "unaryoperation.h"

#include <iostream>
using namespace llvm;

Value *UnaryOperation::codegen() {
	switch(op) {
		case BITWISENOT:
			return Builder.CreateNot(operand->codegen(), "unarynot");
		break;
		case LOGICALNOT:
		{
			// convert the value to i1 then invert it
			Value *v = Builder.CreateTrunc(operand->codegen(), Builder.getInt1Ty(), "tobool");
			return Builder.CreateNot(v, "unarynot");
		}
		break;

		case UNARYMINUS:
			return Builder.CreateNeg(operand->codegen(), "unaryneg");
		break;


		case NOT_UNARY:
		default:
			std::cout << "Unknown compiler state [" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
			return NULL;
		break;
	}
}
