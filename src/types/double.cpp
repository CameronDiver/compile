#include "double.h"

using namespace llvm;

Double::Double(double val=0.0)
	: LanguageType(DOUBLE) {
		value = val;
}

Type *Double::getLLVMType() {
	return Type::getDoubleTy(getGlobalContext());
}

