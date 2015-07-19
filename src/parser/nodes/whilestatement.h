#ifndef PARSE_WHILE_STATEMENT_H
#define PARSE_WHILE_STATEMENT_H

#include "node.h"
#include "genericlist.h"

class WhileStatement : public SyntaxTreeNode {
public:

	SyntaxTreeNode *predicate;
	GenericList *statements;

	WhileStatement(SyntaxTreeNode *pred, SyntaxTreeNode *statementList)
	:	SyntaxTreeNode("While Statement"), predicate(pred) {

		statements = TRY_CAST(statementList, GenericList*);
	}

	std::string getStr() {
		std::stringstream ss;

		ss << "While Statement pred: [" << predicate->getStr() << "]" << std::endl;
		ss << statements->getStr() << std::endl;

		return ss.str();
	}
};

#endif
