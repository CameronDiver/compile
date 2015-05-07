#include "longint.h"

using namespace llvm;

LongInteger::LongInteger(int64_t val=0)
	: LanguageType(LONG_INTEGER) {

	value = val;
}


Type *LongInteger::getLLVMType() {
	return Type::getInt64Ty(getGlobalContext());
}