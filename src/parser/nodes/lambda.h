#ifndef PARSE_LAMBDA_H
#define PARSE_LAMBDA_H

#include "node.h"
#include "argumentlist.h"
#include "genericlist.h"

class LambdaFunction : public SyntaxTreeNode {
public:
	ArgumentList *args;
	GenericList *statements;
	
	LambdaFunction(SyntaxTreeNode *argList, SyntaxTreeNode *stmtList)
	:	SyntaxTreeNode("Lambda Function") {

		args = TRY_CAST(argList, ArgumentList*);

		statements = TRY_CAST(stmtList, GenericList*);
	}

	std::string getStr() {
		std::stringstream ss;
		ss << "Lamba: { |";

		for(auto arg : *args) {
			ss << arg->getStr() << ",";
		}

		ss << " |";
		
		for(auto statement : *statements) {
			if(statement)
				ss << statement->getStr() << ";";
		}


		ss << "}";

		return ss.str();
	}
};


#endif // PARSE_LAMBDA_H
