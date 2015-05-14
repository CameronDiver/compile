#include "symboltable.h"

SymbolTable::SymbolTable(std::string scope) {
	this->scope = scope;
}


bool SymbolTable::hasSymbol(std::string symbol) {
	if(table.find(symbol) == table.end())
		return false;
	return true;
}

Symbol *SymbolTable::getSymbol(std::string symbol) {
	return table.at(symbol);
}

LanguageType *SymbolTable::getType(std::string symbol) {
	// TODO: maybe check it does exist here, evem though the
	// caller should always have done it
	
	return table.at(symbol)->type;
}

void SymbolTable::addSymbol(Symbol *sym) {
	table[sym->getName()] = sym;
}