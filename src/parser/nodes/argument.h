#ifndef PARSE_ARGUMENT_H
#define PARSE_ARGUMENT_H

#include "node.h"
#include "type.h"
#include "symbol.h"

class Argument : public SyntaxTreeNode {
 public:
 	Type *type;
 	Symbol *name;

 	Argument(SyntaxTreeNode *_type, SyntaxTreeNode *_name)
 	:	SyntaxTreeNode("Argument") {
 		type = dynamic_cast<Type *>(_type);
 		if(type == NULL) {
 			// TODO: Errors
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Type but actual class is " << _type->getStr() << std::endl;
 		};
 		name = dynamic_cast<Symbol *>(_name);
 		if(name == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Symbol but actual class is " << _name->getStr() << std::endl;
 		}
 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Argument " << name->getStr();
 		return ss.str();
 	}
};



#endif // PARSE_ARGUMENT_H
