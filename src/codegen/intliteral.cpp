#include "intliteral.h"


llvm::Value *IntLiteral::codegen() {
	// 64 bit integer, TODO: maybe change this so it's not only 64 bits
	return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(value, 64));
}