#ifndef TYPES_H
#define TYPES_H

#include "builtins.h"

class LanguageType {
 public:
 	BuiltinType baseType;

 	LanguageType(BuiltinType t) 
 	: baseType(t) {}

 	virtual llvm::Type *getType()=0;


 	// LanguageType implementations must define all of these
 	// methods for interaction between language types. If a type
 	// does not provide a method for a specific operation with some
 	// other type, the method will return NULL, otherwise the method 
 	// will return the type that the output of the equation will be
 	// addition
 	virtual LanguageType 	*add(LanguageType *operand)=0;
 	// subtraction
 	virtual LanguageType	*sub(LanguageType *operand)=0;
 	// multiplication
 	virtual LanguageType	*mul(LanguageType *operand)=0;
 	// division
 	virtual LanguageType	*div(LanguageType *operand)=0;
 	// variable assignment
 	virtual LanguageType	*assign(LanguageType *operand)=0;
 	// less than
 	virtual LanguageType	*lt(LanguageType *operand)=0;
 	// greater than
 	virtual LanguageType	*gt(LanguageType *operand)=0;
 	// not equal to
 	virtual LanguageType	*neq(LanguageType *operand)=0;
 	// modulo operator
 	virtual LanguageType	*mod(LanguageType *operand)=0;
 	// less than or equal to
 	virtual LanguageType	*lte(LanguageType *operand)=0;
 	// greater than or equal to
 	virtual LanguageType	*gte(LanguageType *operand)=0;
 	// comparison
 	virtual LanguageType	*comp(LanguageType *operand)=0;
 	// logical and
 	virtual LanguageType	*_and(LanguageType *operand)=0;
 	// bitwise and
 	virtual LanguageType	*band(LanguageType *operand)=0;
 	// logical not
 	virtual LanguageType	*_not(LanguageType *operand)=0;
 	// bitwise not
 	virtual LanguageType	*bnot(LanguageType *operand)=0;
 	// logical or
 	virtual LanguageType	*_or(LanguageType *operand)=0;
 	// bitwise or
 	virtual LanguageType	*bor(LanguageType *operand)=0;
 	// logical xor
 	virtual LanguageType	*_xor(LanguageType *operand)=0;
 	// bitwise xor
 	virtual LanguageType	*bxor(LanguageType *operand)=0;

 	// returns true if the langauge type is an integer
 	// type or false otherwise
 	static bool isIntegerType(const class LanguageType *type) {
 		switch(type->baseType) {
 			case INTEGER:
 			case UNSIGNED:
 			case LONG_INTEGER:
 			case LONG_UNSIGNED:
 				return true;
 			break;
 			default:
 				return false;
 			break;
 		}
 	}
};

#endif 