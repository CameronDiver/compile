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


 		type = dynamic_cast<Type *>(_type);
 		if(type == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Type but actual class is " << _type->getStr() << std::endl;
 		};

 		name = dynamic_cast<Symbol *>(_name);
 		if(name == NULL){
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Symbol but actual class is " << _name->getStr() << std::endl;
 		}


 		if(_argList != NULL) {
	 		argList = dynamic_cast<ArgumentList *>(_argList);
	 		if(argList == NULL){
	 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
	 				<< "   Attempted cast to Argument List but actual class is " << _argList->getStr() << std::endl;
	 		}
	 	} else {
	 		argList = NULL;
	 	}

 		statementList = dynamic_cast<GenericList *>(_statementList);
 		if(statementList == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Statement List but actual class is " << _statementList->getStr() << std::endl;
 		}

 		children = statementList->children;
 		std::cout << "Statement list size:" << statementList->children.size() << std::endl;
 		//std::cout << "Statement list [0] = " << statementList->children[0]->getStr() << std::endl;
 		//std::cout << "Statement list [1] = " << statementList->children[1]->getStr() << std::endl;

 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function Definition: " << type->getStr() 
 			<< name->getStr() << " | ";

 		if(argList != NULL) {
	 		for(uint i = 0; i < argList->children.size(); ++i) {
	 			Argument *a = dynamic_cast<Argument *>(argList->children[i]);
	 			ss << a->type->getStr() << " " << a->name->getStr() << ", ";
	 		}
	 	}
 		ss << " | ";

 		return ss.str();
 	}
};


#endif 