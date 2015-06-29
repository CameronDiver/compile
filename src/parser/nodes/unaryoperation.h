#ifndef PARSE_UNARYOP_H
#define PARSE_UNARYOP_H

#include "operators.h"
#include "node.h"

class UnaryExpression : public SyntaxTreeNode {
 public:
 	UnaryOperator op;
 	UnaryExpression(UnaryOperator _op, SyntaxTreeNode *operand)
 	:	SyntaxTreeNode("Unary Operation"), op(_op) {
 		addChild(operand);
 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Unary Operation: " << unaryOpToStr(op);
 		return ss.str();
 	}
};


#endif