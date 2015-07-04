#ifndef PARSE_VARIABLE_DECLARATION
#define PARSE_VARIABLE_DECLARATION

#include "node.h"
#include "type.h"
#include "symbol.h"
#include "binaryoperation.h"

class VariableDeclaration : public SyntaxTreeNode {
public:
	Type *type;
	Symbol *name;
	SyntaxTreeNode *RHS = NULL;

	// Provide 2 constructors, one for with an initialising value, one without
	VariableDeclaration(SyntaxTreeNode *_type, SyntaxTreeNode *_ident)
	: SyntaxTreeNode("Variable Declaration") {
		type = TRY_CAST(_type, Type*);
		name = TRY_CAST(_ident, Symbol*);
	}

	VariableDeclaration(SyntaxTreeNode *_type, SyntaxTreeNode *_ident, SyntaxTreeNode *_RHS)
	:	SyntaxTreeNode("Variable Declaration") {
		
		type = TRY_CAST(_type, Type*);
		name = TRY_CAST(_ident, Symbol*);
		RHS = _RHS;
	}

	std::string getStr() {
		std::stringstream ss;
		ss << "Variable declaration: " << type->getStr() << " " << name->getStr();
		if(RHS)
			ss << " = " << RHS->getStr();
		return ss.str();
	}
};

#endif