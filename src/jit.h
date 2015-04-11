#ifndef JIT_H
#define JIT_H

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "builtins.h"

class JITExecution {
public:
	JITExecution();
private:
	llvm::ExecutionEngine *executionEngine;
};

#endif /* JIT_H */