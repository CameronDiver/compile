#include "bool.h"

Boolean::Boolean(bool val) : LanguageType(BOOLEAN) {
	value = val;
}

Type *Boolean::getLLVMType() {
	return Type::getInt1Ty(getGlobalContext());
}