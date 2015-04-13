#ifndef JIT_H
#define JIT_H

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include <llvm/ExecutionEngine/JIT.h>


#include "builtins.h"

class JITExecution {
public:
	JITExecution();

	// call the main function to get execution going
	int callMain();


private:
	llvm::ExecutionEngine *executionEngine;
};

#endif /* JIT_H */