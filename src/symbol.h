#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "builtins.h"
#include "types/types.h"

class Symbol {
 public:
	LanguageType *type;
	std::string name;

	// TODO:
	std::string defined;


	Symbol(LanguageType *_type, std::string _name)
	: type(_type), name(_name) {

	};


	std::string getName() { return name; }

};


#endif /* SYMBOL_H */