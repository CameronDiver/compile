#ifndef PARSE_FUNCTION_CALL_H
#define PARSE_FUNCTION_CALL_H

#include "node.h"
#include "genericlist.h"

class FunctionCall : public SyntaxTreeNode {
 public:
 	// TODO: Change to Symbol
 	SyntaxTreeNode *name;

 	GenericList *args;


 	FunctionCall(SyntaxTreeNode *_name, SyntaxTreeNode *argList)
 	:	SyntaxTreeNode("Function Call"), name(_name) {
 		if(argList != NULL)
 			args = TRY_CAST(argList, GenericList*);
 		else args = NULL;
 	};


 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function call " << name->getStr() << "( ";
 		if(args)
	 		for(auto arg : *args) {
	 			ss << arg->getStr() << ", ";
	 		}
 		ss << ")";
 		return ss.str();
 	}
};


#endif