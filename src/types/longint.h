#ifndef TYPES_LONG_INT_H
#define TYPES_LONG_INT_H

#include <cstdint>
#include "languagetype.h"

class LongInteger : public LanguageType {
 public:
 	int64_t value;

 	LongInteger(int64_t val=0);

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