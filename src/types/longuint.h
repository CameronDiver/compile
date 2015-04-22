#ifndef TYPE_LONG_UNSIGNED_H
#define TYPE_LONG_UNSIGNED_H

#include <cstdint>
#include "types.h"

class LongUnsigned : public LanguageType {
 public:
 	uint64_t value;

 	LongUnsigned(uint64_t val);

 	llvm::Type *getLLVMType();
};

#endif