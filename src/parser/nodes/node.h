#ifndef PARSE_NODE_H
#define PARSE_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Define a tree node, which will be the root node and every other one
// will subclass this node for easy traversal
class SyntaxTreeNode {
 public:
 	std::string nodeName;
 	SyntaxTreeNode *child;

 	SyntaxTreeNode(std::string name)
 	:	nodeName(name){}

 	virtual void addChild(SyntaxTreeNode *_child){
 		child = _child;
 	}

 	virtual SyntaxTreeNode *getChild() {
 		return child;
 	}


 	/* Get a string representation.
 	 * The default version of this function should be ok for most things
 	 * but other objects will need to override this
 	 */
 	virtual std::string getStr() {
 		return nodeName;
 	}


	virtual bool isList() {
		return false;
	}

 	virtual void printSubtree(unsigned depth=0) {
 		for(int i = 0; i < depth; ++i) std::cout << "   ";
 		std::cout <<  getStr() << std::endl;
 		
		
		if(child != NULL)
			child->printSubtree(depth+1);


 	}


};

// Temporary definition
class CastException {
public:
	CastException(SyntaxTreeNode *obj, std::string destType
#ifdef DEBUG
		, std::string file, int line) 
#else
		)
#endif
{
		std::stringstream ss;
		ss << "Attempted to cast to type " << destType;
		if(obj != NULL) 
			ss << " but node is of type: " << obj->getStr();
		else 
			ss << " but node is NULL.";

		#ifdef DEBUG
			ss << " [" << file << ":" << line << "]";
		#endif

		message = ss.str();
	}

	std::string getMsg(){
		return message;
	}

private:
	std::string message;
};

// Helper macros
#ifdef DEBUG
	#define TRY_CAST(obj, resType) [&obj]()-> resType { resType ret = dynamic_cast<resType>(obj); \
		if((obj) == NULL) throw new CastException(obj, #resType, __FILE__, __LINE__); return ret;}()
#else
	#define TRY_CAST(obj, resType) [&obj]()-> resType { resType ret = dynamic_cast<resType>(obj); \
		if((obj) == NULL) throw new CastException(obj, #resType); return ret;}()
#endif

#endif