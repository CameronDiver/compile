#ifndef FLOAT_TYPE_H 
#define FLOAT_TYPE_H

#include "types.h"

class Float : public LanguageType {
 public:
 	float value;
 	Float(float val);

 	llvm::Type *getLLVMType();
};

#endif