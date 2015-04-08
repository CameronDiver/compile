#include "codegen.h"

using namespace llvm;

std::map<std::string, llvm::Value *> CodeGen::Symbols;

Type *CodeGen::getTypeFromBuiltin(BuiltinType t) {
	switch(t) {
		case INTEGER:
			return Type::getInt64Ty(getGlobalContext());
		break;
		case FLOAT:
			return Type::getFloatTy(getGlobalContext());
		break;

		default:
			return NULL;
		break;
	}
}