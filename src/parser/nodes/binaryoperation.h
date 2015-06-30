#ifndef PARSE_BINOP_H
#define PARSE_BINOP_H

#include <string>
#include <sstream>

#include "operators.h"
#include "node.h"

class BinaryOperation : public SyntaxTreeNode {
 public:
 	Operator op;

 	SyntaxTreeNode *LHS;
 	SyntaxTreeNode *RHS;

 	BinaryOperation(Operator _op, SyntaxTreeNode *_LHS, SyntaxTreeNode *_RHS)
 	:	SyntaxTreeNode("Binary Operation"), op(_op), LHS(_LHS), RHS(_RHS) {	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Binary Operation: " << LHS->getStr() << opToStr(op) << RHS->getStr();
 		
 		return ss.str();
 	}

};


#endif