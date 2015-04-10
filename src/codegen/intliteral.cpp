#include "intliteral.h"


llvm::Value *IntLiteral::codegen() {
	return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, value, false));
}