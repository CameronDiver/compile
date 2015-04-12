#include "ifstatement.h"

#include "codegen.h"
using namespace llvm;


Value *IfStatement::codegen() {
	
	// generate the code for the condition
	Value *condition = predicate->codegen();
	if(condition == NULL) return NULL;

	condition = Builder.CreateICmpNE(condition, 
		ConstantInt::get(CodeGen::getTypeFromBuiltin(INTEGER), 0), "ifcond");


	Function *fn = Builder.GetInsertBlock()->getParent();

	// create and insert the true code, but only create the other blocks so
	// they can be inserted in the correct position later
	BasicBlock *trueBlock 	= BasicBlock::Create(getGlobalContext(), "iftrue", fn);
	BasicBlock *falseBlock	= BasicBlock::Create(getGlobalContext(), "iffalse");
	BasicBlock *mergeBlock	= BasicBlock::Create(getGlobalContext(), "ifmerge");

	// create the branch
	Builder.CreateCondBr(condition, trueBlock, falseBlock);

	Builder.SetInsertPoint(trueBlock);

	Value *trueV = NULL;
	for(unsigned i = 0; i < statements.size(); ++i){
		trueV = statements[i]->codegen();
	}

	Builder.CreateBr(mergeBlock);
	trueBlock = Builder.GetInsertBlock();

	// now do the else block
	fn->getBasicBlockList().push_back(falseBlock);
	Builder.SetInsertPoint(falseBlock);

	Value *falseV = NULL;
	for(unsigned i = 0; i < elseStatements.size(); ++i) {
		falseV = elseStatements[i]->codegen();
	}

	Builder.CreateBr(mergeBlock);
	falseBlock = Builder.GetInsertBlock();

	fn->getBasicBlockList().push_back(mergeBlock);
	Builder.SetInsertPoint(mergeBlock);

	// PHINode *phi = Builder.CreatePHI(CodeGen::getTypeFromBuiltin(INTEGER), 2, "iftmp");
	// phi->addIncoming(trueV, trueBlock);
	// phi->addIncoming(falseV, falseBlock);
	Value *v = Builder.CreateAdd(CodeGen::getInitialiser(INTEGER), CodeGen::getInitialiser(INTEGER), "ifdummyadd");
	return v;
}