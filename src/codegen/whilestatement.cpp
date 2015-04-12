#include "whilestatement.h"


#include "codegen.h"
using namespace llvm;

Value *WhileStatement::codegen() {
	Function *fn = Builder.GetInsertBlock()->getParent();

	BasicBlock *pred = BasicBlock::Create(getGlobalContext(), "looppred", fn);
	BasicBlock *loop = BasicBlock::Create(getGlobalContext(), "loopbody");
	BasicBlock *afterLoop = BasicBlock::Create(getGlobalContext(), "loopafter");

	// need to create a conditional branch for the predicate
	Builder.SetInsertPoint(pred);

	Value *predValue= predicate->codegen();
	if(predValue == NULL) return NULL;

	// create the condition
	Value *condition = Builder.CreateICmpNE(predValue, 
		ConstantInt::get(CodeGen::getTypeFromBuiltin(INTEGER), 0),
		"whilecond");

	// create the branching condition
	Builder.CreateCondBr(condition, loop, afterLoop);
	
	// start adding in the internal statements
	fn->getBasicBlockList().push_back(loop);
	Builder.SetInsertPoint(loop);


	for(unsigned i = 0; i < statements.size(); ++i) {
		statements[i]->codegen();
	}

	// jump back to before the predicate test now
	Builder.CreateBr(pred);

	fn->getBasicBlockList().push_back(afterLoop);
	Builder.SetInsertPoint(afterLoop);

	return Builder.CreateAdd(CodeGen::getInitialiser(INTEGER), CodeGen::getInitialiser(INTEGER), "whiledummyadd");
}