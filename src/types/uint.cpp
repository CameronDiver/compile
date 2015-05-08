#include "uint.h"

using namespace llvm;

UnsignedInteger::UnsignedInteger(uint32_t value):
LanguageType(UNSIGNED) {
	this->value = value;
}

Type *UnsignedInteger::getLLVMType() {
	return Type::getInt32Ty(getGlobalContext());
}