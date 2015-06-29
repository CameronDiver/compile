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
 	std::vector<SyntaxTreeNode *> children;

 	SyntaxTreeNode(std::string name)
 	:	nodeName(name){}

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

class CastException {
public:
	CastException(std::string msg)
	:	message(msg) {}

	std::string getMsg(){
		return message;
	}

private:
	std::string message;
};

// Helper macros
#define TRY_CAST(obj, resType) [&obj]()-> resType { resType ret = dynamic_cast<resType>(obj); \
	if((obj) == NULL) throw new CastException("TODO"); return ret;}()

#endif