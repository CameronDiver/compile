#ifndef PARSE_IF_STATEMENT_H
#define PARSE_IF_STATEMENT_H

#include "node.h"
#include "genericlist.h"

class IfStatement : public SyntaxTreeNode {
public:
	SyntaxTreeNode *predicate;
	GenericList *statements;
	GenericList *elseStatements;

	IfStatement(SyntaxTreeNode *pred, SyntaxTreeNode *_statements)
	:	SyntaxTreeNode("If Statement"), predicate(pred) {

		statements = TRY_CAST(_statements, GenericList*);
		elseStatements = NULL;
	}

	IfStatement(SyntaxTreeNode *pred, SyntaxTreeNode *_statements, SyntaxTreeNode *elseStmts)
	:	SyntaxTreeNode("If Statement"), predicate(pred) {
		statements = TRY_CAST(_statements, GenericList*);
		elseStatements = TRY_CAST(elseStmts, GenericList*);
	}


	std::string getStr() {
		std::stringstream ss;
		ss << "If statement: pred: [" << predicate->getStr() << "]" << std::endl
			<< statements->getStr() << std::endl;
		if(elseStatements)
			ss << elseStatements->getStr() << std::endl;
		return ss.str();
	}
};

#endif