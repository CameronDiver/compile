#include "codegen.h"

using namespace llvm;

std::map<std::string, llvm::Value *> CodeGen::Symbols;


CodeGen::CodeGen(AbstractSyntaxTree *tree) {
	for(unsigned i = 0; i < tree->functions.size(); ++i) {
		FunctionDefinition *fn = tree->functions[i];
		currentFn = fn;

		Value *f = fn->codegen();
		
	}
}

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

AllocaInst *CodeGen::createEntryBlockAlloca(Function *fn, const std::string name, BuiltinType t) {

	IRBuilder<> tempBuilder(fn->getEntryBlock(), fn->getEntryBlock().begin());

	return tempBuilder.CreateAlloca(getTypeFromBuiltin(t), 0, name);
}