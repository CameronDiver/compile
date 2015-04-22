#ifndef TYPE_DOUBLE_H
#define TYPE_DOUBLE_H

#include "types.h"

class Double : public LanguageType {
 public:
 	double value;

 	Double(double val);

 	llvm::Type *getLLVMType();
};

#endif 