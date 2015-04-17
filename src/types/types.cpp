#include "types.h"

llvm::Type *LanguageType::getType(){
	switch(BaseType) {
		case INTEGER:
		break;
		case UNSIGNED:
		break;
		case FLOAT:
		break;
		case DOUBLE:
		break;
		case LONG_INTEGER:
		break;
		case LONG_UNSIGNED:
		break;
		case BOOLEAN:
		break;
		case POINTER:
		break;

		case TYPE_UNKNOWN:
		default:
		break;
	}
}