#include <iostream>
#include <map>

#include "builtins.h"

static std::map<std::string, BuiltinType> 	types;
static std::map<std::string, Keyword>		keywords;

void installTypes() {
	types.insert(std::pair<std::string, BuiltinType>("int", INTEGER));
	types.insert(std::pair<std::string, BuiltinType>("float", FLOAT));
}

void installKeywords() {
	keywords.insert(std::pair<std::string, Keyword>("end", END));
}

BuiltinType typeLookup(std::string name) {
	if(types.find(name) == types.end())
		return TYPE_UNKNOWN;
	else 
		return types.at(name);

}

int main(int argc, char *argv[]) {
	// intialisation
	installTypes();
	installKeywords();
}