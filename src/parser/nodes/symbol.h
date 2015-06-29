#ifndef PARSE_SYMBOL_H
#define PARSE_SYMBOL_H

#include "node.h"

class Symbol : public SyntaxTreeNode {
 public:
 	std::string symbol;
 	Symbol(char *_sym)
 	:	SyntaxTreeNode("Symbol"), symbol(_sym) {
 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Symbol: " << symbol;
 		return ss.str();
 	}
};


#endif