#include "longuint.h"

using namespace llvm;

LongUnsigned::LongUnsigned(uint64_t val)
	: LanguageType(LONG_UNSIGNED) {

	value = val;
}

Type *LongUnsigned::getLLVMType() {
	return Type::getInt64Ty(getGlobalContext());
}