#include "whilestatement.h"


#include "codegen.h"
using namespace llvm;

Value *WhileStatement::codegen() {
	Function *fn = Builder.GetInsertBlock()->getParent();

	BasicBlock *pred = BasicBlock::Create(getGlobalContext(), "looppred", fn);
	BasicBlock *loop = BasicBlock::Create(getGlobalContext(), "loopbody");
	BasicBlock *afterLoop = BasicBlock::Create(getGlobalContext(), "loopafter");

	// create a jump to the predicate
	Builder.CreateBr(pred);

	// need to create a conditional branch for the predicate
	Builder.SetInsertPoint(pred);

	Value *predValue= predicate->codegen();
	if(predValue == NULL) return NULL;

	// create the condition
	Value *condition = Builder.CreateICmpNE(predValue, 
		ConstantInt::getFalse(Type::getInt1Ty(getGlobalContext())),
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

	return CodeGen::createNoOp();
}