#include "jit.h"


using namespace llvm;

JITExecution::JITExecution() {
	// create the execution engine and register the module with it
	executionEngine = EngineBuilder(module).create();
}