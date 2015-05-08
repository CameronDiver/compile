#include "sint.h"

using namespace llvm;

SignedInteger::SignedInteger(int32_t value)
:LanguageType(INTEGER) {
	this->value = value;
}

Type *SignedInteger::getLLVMType() {
	return Type::getInt32Ty(getGlobalContext());
}