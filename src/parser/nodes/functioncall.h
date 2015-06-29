#ifndef PARSE_FUNCTION_CALL_H
#define PARSE_FUNCTION_CALL_H

#include "node.h"

class FunctionCall : public SyntaxTreeNode {
 public:
 	SyntaxTreeNode *name;
 	FunctionCall(SyntaxTreeNode *_name, SyntaxTreeNode *argList)
 	:	SyntaxTreeNode("Function Call"), name(_name) {
 		if(argList != NULL){
 			for(uint i = 0; i < argList->children.size(); ++i) {
 				addChild(argList->children[i]);
 			};
 		}
 	};


 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function call " << name->getStr();
 		return ss.str();
 	}
};


#endif