#ifndef TYPE_DOUBLE_H
#define TYPE_DOUBLE_H

#include "types.h"

class Double : public LanguageType {
 public:
 	double value;

 	Double(double val=0.0);

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