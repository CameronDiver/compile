#include "codegen.h"

using namespace llvm;

std::map<std::string, Value *> CodeGen::Symbols;


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
			return Type::getInt32Ty(getGlobalContext());
		break;
		case FLOAT:
			return Type::getFloatTy(getGlobalContext());
		break;

		default:
			std::cout << "Wrong type: " << __FILE__ << "[" << __LINE__ << "]" << std::endl;
			return NULL;
		break;
	}
}

Value *CodeGen::getInitialiser(BuiltinType t) {
	switch(t) {
		case INTEGER:
			return ConstantInt::get(getTypeFromBuiltin(t), 0);
		break;
		case FLOAT:
			return ConstantFP::get(getGlobalContext(), APFloat(0.0));
		break;

		default:
			std::cout << "Wrong type: " << __FILE__ << "[" << __LINE__ << "]" << std::endl;
			return NULL;
		break;
	}
}

AllocaInst *CodeGen::createEntryBlockAlloca(Function *fn, const std::string name, BuiltinType t) {

	IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());

	return tempBuilder.CreateAlloca(getTypeFromBuiltin(t), 0, name);
}

Value *CodeGen::createNoOp() {
	return Builder.CreateBitCast(getInitialiser(INTEGER), getTypeFromBuiltin(INTEGER), "NoOp");
}