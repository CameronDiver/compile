#ifndef AST_IF_STATEMENT_H
#define AST_IF_STATEMENT_H

#include <vector>
#include <string>
#include <sstream>
#include "expression.h"

class IfStatement : public Expression {
public:
	Expression *predicate;
	std::vector<Expression *> statements;

	IfStatement(Expression *pred, std::vector<Expression *> _statements)
	: predicate(pred), statements(_statements) {}

	llvm::Value *codegen(){std::cout << "From codegen in ifstatement\n";return NULL;}

#if defined(DEBUG)
	std::string prettyPrint() {
		std::stringstream ss("");
		ss << "If statement, predicate \n\t[" << predicate->prettyPrint() << "]\n";
		ss << "\tStatements\n";
		for(unsigned i = 0; i < statements.size(); ++i) {
			ss << "\t\t" << statements[i]->prettyPrint() << "\n";
		}

		return ss.str();
	}
#endif
};

#endif
