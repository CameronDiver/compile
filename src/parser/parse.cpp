#include <iostream>
#include <cstdio>
#include "parse.h"


SyntaxTreeNode *root;
PathManager pathManager;

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


int main(int argc, char *argv[]) {

	pathManager.addPath("./");

	if(argc >= 2){
		yyin = pathManager.openImport(argv[1]);
		//fopen(argv[1], "r");
	}



	// Setup a root node for the tree to begin building from
	root = new SyntaxTreeNode("Root");

	try {
		yyparse();
	} catch(CastException *c) {
		std::cout << "Received a cast exception: " << c->getMsg() << std::endl;
	}

	root->printSubtree();

	return 0;
}
