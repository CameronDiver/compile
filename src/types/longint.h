#ifndef TYPES_LONG_INT_H
#define TYPES_LONG_INT_H

#include <cstdint>
#include "types.h"

class LongInteger : public LanguageType {
 public:
 	int64_t value;

 	LongInteger(int64_t val);

 	llvm::Type *getLLVMType();
};


#endif