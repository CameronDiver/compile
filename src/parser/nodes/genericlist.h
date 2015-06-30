#ifndef PARSE_GENERIC_LIST_H
#define PARSE_GENERIC_LIST_H

#include "list.h"

class GenericList : public NodeList<SyntaxTreeNode> {
public:
	GenericList(SyntaxTreeNode *child)
	:	NodeList("List", child) {}

	GenericList()
	:	NodeList("List") {}
};

#endif // PARSE_GENERIC_LIST_H
