#ifndef UNSIGNED_INT_TYPE_H
#define UNSIGNED_INT_TYPE_H

#include "types.h"

// unsigned 32 bit integer
class UnsignedInteger : public LanguageType {
 public:
 	uint32_t value;
 	UnsignedInteger(uint32_t value=0);

 	llvm::Type *getLLVMType();

 	LanguageType *add(LanguageType *operand);
 	LanguageType *sub(LanguageType *operand);
 	LanguageType *mul(LanguageType *operand);
 	LanguageType *div(LanguageType *operand);
 	LanguageType *assign(LanguageType *operand);
 	LanguageType *lt(LanguageType *operand);
 	LanguageType *gt(LanguageType *operand);
 	LanguageType *neq(LanguageType *operand);
 	LanguageType *mod(LanguageType *operand);
 	LanguageType *lte(LanguageType *operand);
 	LanguageType *gte(LanguageType *operand);
 	LanguageType *comp(LanguageType *operand);
 	LanguageType *_and(LanguageType *operand);
 	LanguageType *band(LanguageType *operand);
 	LanguageType *_not(LanguageType *operand);
 	LanguageType *bnot(LanguageType *operand);
 	LanguageType *_or(LanguageType *operand);
 	LanguageType *bor(LanguageType *operand);
 	LanguageType *_xor(LanguageType *operand);
 	LanguageType *bxor(LanguageType *operand);
};

#endif