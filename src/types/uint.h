#ifndef UNSIGNED_INT_TYPE_H
#define UNSIGNED_INT_TYPE_H

#include "types.h"

// unsigned 32 bit integer
class UnsignedInteger : public LanguageType {
 public:
 	uint32_t value;
 	UnsignedInteger(uint32_t value);

 	llvm::Type *getLLVMType();
};

#endif