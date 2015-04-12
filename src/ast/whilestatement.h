#ifndef AST_WHILE_STATEMENT_H
#define AST_WHILE_STATEMENT_H

#include <vector>
#include <string>
#include <sstream>
#include "expression.h"

class WhileStatement : public Expression {
public:
	Expression *predicate;
	std::vector<Expression *> statements;

	WhileStatement(Expression *pred, std::vector<Expression *> _statements)
	: predicate(pred), statements(_statements){}

	llvm::Value *codegen() { return NULL; }

	#if defined(DEBUG)
	std::string prettyPrint() {
		stringstream ss("");
		ss << "While loop, pred [ " << predicate->prettyPrint() << "]\n";
		ss << "Statements:\n";
		for(unsigned i = 0; i < statements.size(); ++i) {
			ss << "\t" << statements[i]->prettyPrint() << "\n";
		}
		return ss.str();
	}
	#endif
};

#endif