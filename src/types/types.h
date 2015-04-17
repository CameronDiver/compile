#ifndef TYPES_H
#define TYPES_H

#include "builtins.h"

class LanguageType {
 public:
 	BuiltinType BaseType;

 	LanguageType(BuiltinType t) 
 	: BaseType(t) {}

 	virtual llvm::Type *getType();
};

#endif 