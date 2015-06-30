#include <iostream>
#include <cstdio>
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

std::string unaryOpToStr(UnaryOperator op) {
	switch(op) {
		case UNARY_NOT:
			return "not";
		case UNARY_BNOT:
			return "~";
		case UNARY_PREINC:
			return "pre ++";
		case UNARY_PREDEC:
			return "pre --";
		case UNARY_POSTINC:
			return "post ++";
		case UNARY_POSTDEC:
			return "post --";
		case UNARY_PLUS:
			return "+";
		case UNARY_MINUS:
			return "-";
	}
}

// current is the current node that is being added to
SyntaxTreeNode *root, *currentNode;

void setCurrentNode(SyntaxTreeNode *node) {
	currentNode = node;
}


int main(int argc, char *argv[]) {
	if(argc >= 2){
		yyin = fopen(argv[1], "r");
	}
	


	// Setup a root node for the tree to begin building from
	root = new SyntaxTreeNode("Root");
	currentNode = root;

	try {
		yyparse();
	} catch(CastException *c) {
		std::cout << "Received a cast exception: " << c->getMsg() << std::endl;
	}

	root->printSubtree();

	return 0;
}