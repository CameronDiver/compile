#include <iostream>
#include "parse.h"

std::string opToStr(Operator op) {
	switch(op){
		case OP_PLUS:
			return "+";
		case OP_MINUS:
			return "-";
		case OP_MULT:
			return "*";
		case OP_DIV:
			return "/";
		case OP_COMP:
			return "==";
		case OP_LTE:
			return "<=";
		case OP_GTE:
			return ">=";
		case OP_NEQ:
			return "!=";
		case OP_LT:
			return "<";
		case OP_GT:
			return ">";
		case OP_PLUSEQ:
			return "+=";
		case OP_MINUSEQ:
			return "-=";
		case OP_MULTEQ:
			return "*=";
		case OP_DIVEQ:
			return "/=";
		case OP_ASSIGN:
			return "=";
		default:
			return "TODO";
	}
}

// current is the current node that is being added to
SyntaxTreeNode *root, *currentNode;

void setCurrentNode(SyntaxTreeNode *node) {
	currentNode = node;
}


int main(int argc, char *argv[]) {
	// Setup a root node for the tree to begin building from
	root = new SyntaxTreeNode("Root");
	currentNode = root;

	yyparse();

	root->printSubtree();

	return 0;
}