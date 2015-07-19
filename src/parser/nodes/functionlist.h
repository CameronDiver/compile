#ifndef PARSE_FUNCTION_LIST_H
#define PARSE_FUNCTION_LIST_H

#include "list.h"
#include "functiondef.h"

class FunctionList : public NodeList<FunctionDef> {
public:
	FunctionList(SyntaxTreeNode *definition)
	:	NodeList("Function List", definition) {
	}

	FunctionList()
	:	NodeList("Function List") {
	}
};

#endif
