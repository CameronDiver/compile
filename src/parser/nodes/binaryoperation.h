#ifndef PARSE_BINOP_H
#define PARSE_BINOP_H

#include <string>
#include <sstream>

#include "operators.h"
#include "node.h"

class BinaryOperation : public SyntaxTreeNode {
 public:
 	/* TODO: custom type for operators */
 	Operator op;
 	BinaryOperation(Operator _op, SyntaxTreeNode *LHS, SyntaxTreeNode *RHS)
 	:	SyntaxTreeNode("Binary Operation"), op(_op) {
 			addChild(LHS);
 			addChild(RHS);
 		}; 

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Binary Operation: " << opToStr(op);
 		//ss << op;
 		return ss.str();
 	}

};


#endif