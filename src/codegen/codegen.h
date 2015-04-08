#ifndef CODEGEN_H
#define CODEGEN_H

#include <map>
#include <string>

#include "builtins.h"

class CodeGen {

public:
	static std::map<std::string, llvm::Value *> Symbols;



	static llvm::Type *getTypeFromBuiltin(BuiltinType t);

};

#endif