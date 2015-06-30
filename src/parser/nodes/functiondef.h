#ifndef PARSE_FUNCTION_DEF_H
#define PARSE_FUNCTION_DEF_H

#include "node.h"
#include "type.h"
#include "symbol.h"
#include "argumentlist.h"
#include "genericlist.h"

class FunctionDef : public SyntaxTreeNode {
 public:
 	/* TODO: Process these to types representing what they are */
 	Type *type;
 	Symbol *name;
 	ArgumentList *argList;
 	GenericList *statementList;


 	FunctionDef(SyntaxTreeNode *_type, SyntaxTreeNode *_name, 
 	  SyntaxTreeNode *_argList, SyntaxTreeNode *_statementList)
 	:	SyntaxTreeNode("Function Definition") {

 		type = TRY_CAST(_type, Type*);
 		name = TRY_CAST(_name, Symbol*);

 		if(_argList)
 			argList = TRY_CAST(_argList, ArgumentList*);

 		statementList = TRY_CAST(_statementList, GenericList*);


 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function Definition: " << type->getStr() 
 			<< name->getStr() << " | ";

 		if(argList != NULL) {
	 		for(auto arg: *argList) {
	 			// TODO: Fix trailing comma
	 			ss << " " << arg->getStr() << ",";
	 		}
	 	}
 		ss << " | ";
 		
 		for(auto statement : *statementList) {
 			ss << statement->getStr() << std::endl;
 		}

 		return ss.str();
 	}
};


#endif 