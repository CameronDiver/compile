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

typedef enum {
	UNARY_NOT,
	UNARY_BNOT,
	UNARY_PREINC,
	UNARY_PREDEC,
	UNARY_POSTINC,
	UNARY_POSTDEC,
	UNARY_PLUS,
	UNARY_MINUS
} UnaryOperator;

int yyparse();
extern FILE *yyin;
std::string opToStr(Operator op);
std::string unaryOpToStr(UnaryOperator op);

// Define a tree node, which will be the root node and every other one
// will subclass this node for easy traversal
class SyntaxTreeNode {
 public:
 	std::string nodeName;
 	std::vector<SyntaxTreeNode *> children;

 	SyntaxTreeNode(std::string name) :
 		nodeName(name){
 		};

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
 	:	SyntaxTreeNode("Integer") {
 		// Get number from image
 		value = intFromImage(image);
 	};


 	int intFromImage(char *image) {
 		return atoi(image);
 	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Integer: ";
 		ss << value;
 		return ss.str();
 	}
};

class Float : public SyntaxTreeNode {
 public:
 	double value;
 	Float(char *image)
 	:	SyntaxTreeNode("Float") {
 		value = floatFromImage(image);
 	};

 	double floatFromImage(char *image) {
 		return atof(image);
 	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Float: " << value;
 		return ss.str();
 	}
};

class BinaryOperation : public SyntaxTreeNode {
 public:
 	/* TODO: custom type for operators */
 	Operator op;
 	BinaryOperation(Operator _op, SyntaxTreeNode *LHS, SyntaxTreeNode *RHS)
 	:	SyntaxTreeNode("Binary Operation"), op(_op) {
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

class ExpressionList : public SyntaxTreeNode {
 public:
 	ExpressionList(SyntaxTreeNode *expression)
 	:	SyntaxTreeNode("Expression List") {
 			addChild(expression);
 		};

};

class UnaryExpression : public SyntaxTreeNode {
 public:
 	UnaryOperator op;
 	UnaryExpression(UnaryOperator _op, SyntaxTreeNode *operand)
 	:	SyntaxTreeNode("Unary Operation"), op(_op) {
 		addChild(operand);
 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Unary Operation: " << unaryOpToStr(op);
 		return ss.str();
 	}
};

class FunctionCall : public SyntaxTreeNode {
 public:
 	SyntaxTreeNode *name;
 	FunctionCall(SyntaxTreeNode *_name, SyntaxTreeNode *argList)
 	:	SyntaxTreeNode("Function Call"), name(_name) {
 		if(argList != NULL){
 			for(uint i = 0; i < argList->children.size(); ++i) {
 				addChild(argList->children[i]);
 			};
 		}
 	};


 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function call " << name->getStr();
 		return ss.str();
 	}
};

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

class String : public SyntaxTreeNode {
 public:
 	std::string image;
 	String(char *_image)
 	:	SyntaxTreeNode("String"), image(_image) {
 		// TODO: Escaping
 	};


 	std::string getStr() {
 		std::stringstream ss;
 		ss << "String " << image;
 		return ss.str();
 	}
};

class StatementList : public SyntaxTreeNode {
 public:
 	StatementList()
 	:	SyntaxTreeNode("Statement List") {
 	};
};

#endif