#ifndef PARSE_ARGUMENT_LIST_H
#define PARSE_ARGUMENT_LIST_H

#include "list.h"
#include "argument.h"

class ArgumentList : public NodeList<Argument> {
 public:
 	ArgumentList(SyntaxTreeNode *arg)
 	:	NodeList("Argument List") {}
};


#endif // PARSE_ARGUMENT_LIST_H
