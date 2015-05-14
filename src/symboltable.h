#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include <string>
#include <map>

class SymbolTable {
 public:
 	std::map<std::string, Symbol *> table;
 	std::string scope;

 	SymbolTable(std::string scope="global");

 	bool hasSymbol(std::string symbol);
 	Symbol *getSymbol(std::string symbol);
 	LanguageType *getType(std::string symbol);

 	void addSymbol(Symbol *sym);
};

#endif