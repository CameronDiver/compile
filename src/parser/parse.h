#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <cstdint>
#include <cstdio>
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
 	StatementList(SyntaxTreeNode *entry)
 	:	SyntaxTreeNode("Statement List") {
 		if(entry != NULL) {
 			addChild(entry);
 		};
 	};
};

class Type : public SyntaxTreeNode {
 public:
	typedef enum {
		INT32,
		UINT32,
		INT8,
		UINT8,
		INT16,
		UINT16,
		BOOLEAN,
		FLOAT,
		DOUBLE,
		STRING,
		CHAR,
		INT64,
		UINT64,
		VOID,

		CUSTOM
	} LanguageType;

	LanguageType type;
	std::string image;

	Type(LanguageType t)
	: 	SyntaxTreeNode("Type"), type(t) {
	}

	Type(char *_image)
	:	SyntaxTreeNode("Custom Type"), type(CUSTOM), image(_image) {

	}

};

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

class ArgumentList : public SyntaxTreeNode {
 public:

 	ArgumentList(SyntaxTreeNode *arg)
 	:	SyntaxTreeNode("Argument List") {
#if defined(DEBUG)
 		Argument *a = dynamic_cast<Argument *>(arg);
 		if(a == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Argument but actual class is " << arg->getStr() << std::endl;
 		}
#endif

 		addChild(arg);
 	};
};

class FunctionDef : public SyntaxTreeNode {
 public:
 	/* TODO: Process these to types representing what they are */
 	Type *type;
 	Symbol *name;
 	ArgumentList *argList;
 	StatementList *statementList;


 	FunctionDef(SyntaxTreeNode *_type, SyntaxTreeNode *_name, 
 	  SyntaxTreeNode *_argList, SyntaxTreeNode *_statementList)
 	:	SyntaxTreeNode("Function Definition") {


 		type = dynamic_cast<Type *>(_type);
 		if(type == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Type but actual class is " << _type->getStr() << std::endl;
 		};

 		name = dynamic_cast<Symbol *>(_name);
 		if(name == NULL){
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Symbol but actual class is " << _name->getStr() << std::endl;
 		}


 		if(_argList != NULL) {
	 		argList = dynamic_cast<ArgumentList *>(_argList);
	 		if(argList == NULL){
	 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
	 				<< "   Attempted cast to Argument List but actual class is " << _argList->getStr() << std::endl;
	 		}
	 	} else {
	 		argList = NULL;
	 	}

 		statementList = dynamic_cast<StatementList *>(_statementList);
 		if(statementList == NULL) {
 			std::cout << "Cast error " << __FILE__ << ":" << __LINE__ << std::endl
 				<< "   Attempted cast to Statement List but actual class is " << _statementList->getStr() << std::endl;
 		}

 		children = statementList->children;
 		std::cout << "Statement list size:" << statementList->children.size() << std::endl;
 		//std::cout << "Statement list [0] = " << statementList->children[0]->getStr() << std::endl;
 		//std::cout << "Statement list [1] = " << statementList->children[1]->getStr() << std::endl;

 	};

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Function Definition: " << type->getStr() 
 			<< name->getStr() << " | ";

 		if(argList != NULL) {
	 		for(uint i = 0; i < argList->children.size(); ++i) {
	 			Argument *a = dynamic_cast<Argument *>(argList->children[i]);
	 			ss << a->type->getStr() << " " << a->name->getStr() << ", ";
	 		}
	 	}
 		ss << " | ";

 		return ss.str();
 	}
};

#endif