#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


typedef enum {
	OP_PLUS,
	OP_MINUS,
	OP_MULT,
	OP_DIV,
	OP_MOD,

	OP_COMP,
	OP_LTE,
	OP_GTE,
	OP_NEQ,

	OP_LT,
	OP_GT,

	OP_PLUSEQ,
	OP_MINUSEQ,
	OP_MULTEQ,
	OP_DIVEQ,
	OP_ASSIGN

} Operator;

int yyparse();
std::string opToStr(Operator op);

// Define a tree node, which will be the root node and every other one
// will subclass this node for easy traversal
class SyntaxTreeNode {
 public:
 	std::string nodeName;
 	std::vector<SyntaxTreeNode *> children;

 	SyntaxTreeNode(std::string name) :
 		nodeName(name){};

 	void addChild(SyntaxTreeNode *child) {
 		children.push_back(child);
 	}

 	std::vector<SyntaxTreeNode *> getChildren() {
 		return children;
 	}


 	/* Get a string representation.
 	 * The default version of this function should be ok for most things
 	 * but other objects will need to override this
 	 */
 	virtual std::string getStr() {
 		return nodeName;
 	}

 	void printSubtree(int depth=0) {
 		for(int i = 0; i < depth; ++i) std::cout << "   ";
 		std::cout <<  getStr() << std::endl;
 		for(uint j = 0; j < children.size(); ++j) {
 			children[j]->printSubtree(depth+1);
 		}
 	}


};

extern SyntaxTreeNode *root;
extern SyntaxTreeNode *currentNode;

void setCurrentNode(SyntaxTreeNode *node);

/* TODO: move these to their own files eventually */
class Integer : public SyntaxTreeNode {
 public:
 	uint64_t value;
 	Integer(char *image, int base=10)
 		: SyntaxTreeNode("Integer") {
 		// Get number from image
 		value = getIntFromImage(image);
 	};


 	int getIntFromImage(char *image) {
 		return atoi(image);
 	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Integer: ";
 		ss << value;
 		return ss.str();
 	}
};

class BinaryOperation : public SyntaxTreeNode {
 public:
 	/* TODO: custom type for operators */
 	Operator op;
 	BinaryOperation(Operator _op, SyntaxTreeNode *LHS, SyntaxTreeNode *RHS)
 		: SyntaxTreeNode("Binary Operation"), op(_op) {
 			addChild(LHS);
 			addChild(RHS);
 		}; 

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Binary Operation: " << opToStr(op);
 		//ss << op;
 		return ss.str();
 	}

};
#endif