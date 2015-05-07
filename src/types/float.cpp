#include "float.h"

using namespace llvm;

Float::Float(float val=0.0) : LanguageType(FLOAT) {
	value = val;
}

Type *Float::getLLVMType() {
	return Type::getFloatTy(getGlobalContext());
}