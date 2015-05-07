#include "bool.h"

Boolean::Boolean(bool val=false) : LanguageType(BOOLEAN) {
	value = val;
}

Type *Boolean::getLLVMType() {
	return Type::getInt1Ty(getGlobalContext());
}