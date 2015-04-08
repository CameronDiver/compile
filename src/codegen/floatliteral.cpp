#include "floatliteral.h"

llvm::Value *FloatLiteral::codegen() {
	return llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat(value));
}