#ifndef CODEGEN_H
#define CODEGEN_H

#include <map>
#include <string>

#include "builtins.h"
#include "ast.h"

// the current function
extern FunctionDefinition *currentFn;
extern llvm::Function *currentFnllvm;

class CodeGen {

public:
	static std::map<std::string, llvm::Value *> Symbols;
	static llvm::Type *getTypeFromBuiltin(BuiltinType t);
	// create a allocate instruction for creating variables on the stack
	static llvm::AllocaInst *
		createEntryBlockAlloca(llvm::Function *fn, const std::string name, BuiltinType t);

	static llvm::Value *getInitialiser(BuiltinType t);
	static llvm::Value *createNoOp();


	CodeGen(AbstractSyntaxTree *tree);

};

#endif