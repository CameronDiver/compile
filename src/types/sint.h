#ifndef SIGNED_INT_TYPE_H
#define SIGNED_INT_TYPE_H

#include "types.h"
#include <cstdint>

// signed 32 bit integer
class SignedInteger : public LanguageType {
 public:
 	int32_t value;
 	SignedInteger(int32_t value);

 	llvm::Type *getLLVMType();
};

#endif