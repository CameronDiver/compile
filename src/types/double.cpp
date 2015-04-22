#include "double.h"

using namespace llvm;

Double::Double(double val)
	: LanguageType(DOUBLE) {
		value = val;
}

Type *Double::getLLVMType() {
	return Type::getDoubleTy(getGlobalContext());
}

