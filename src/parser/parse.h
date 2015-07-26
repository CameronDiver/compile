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
#include "pathman.h"


int yyparse();
extern FILE *yyin;

extern SyntaxTreeNode *root;

void setCurrentNode(SyntaxTreeNode *node);



#endif
