#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "nodes/nodes.h"

int yyparse();
extern FILE *yyin;

extern SyntaxTreeNode *root;
extern SyntaxTreeNode *currentNode;

void setCurrentNode(SyntaxTreeNode *node);

/* TODO: move these to their own files eventually */





#endif