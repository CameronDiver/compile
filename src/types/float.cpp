#include "float.h"

using namespace llvm;

Float::Float(float val) : LanguageType(FLOAT) {
	value = val;
}

Type *Float::getLLVMType() {
	return Type::getFloatTy(getGlobalContext());
}