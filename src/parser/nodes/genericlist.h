#ifndef PARSE_GENERIC_LIST_H
#define PARSE_GENERIC_LIST_H

#include <vector>

#include "node.h"

// Inherit from SyntaxTreeNode instread of NodeList,
// as using the base SyntaxTreeNode class as the template
// for NodeList produces extra checking code which isn't
// necessary (or helpful)
// 
class GenericList : public SyntaxTreeNode {
public:
	GenericList(SyntaxTreeNode *child)
	:	SyntaxTreeNode("List") {
		addChild(child);
	}

	GenericList()
	:	SyntaxTreeNode("List") {}

	const unsigned size() const {
		return children.size();
	}

	void addChild(SyntaxTreeNode *child) {
		children.push_back(child);
	}

	std::vector<SyntaxTreeNode *> getChildren() const {
		return children;
	}

	std::string getStr() {
		std::stringstream ss;
		ss << "List:\n\t";
		for(auto c : children) {
			ss << c->getStr() << ",\n\t";
		}

		return ss.str();
	}

	SyntaxTreeNode *operator[](unsigned idx) {
		return children[idx];
	}

	std::vector<SyntaxTreeNode *>::iterator begin() {
		return children.begin();
	}

	std::vector<SyntaxTreeNode *>::iterator end() {
		return children.end();
	}

	bool isList() {
		return true;
	}
 
	void printSubtree(unsigned depth=0) {
		for(auto c : children) {
			for(uint i = 0; i < depth; ++i) std::cout << "   ";
			std::cout << c->getStr() << "\n";
		}
	}

private:
	std::vector<SyntaxTreeNode *> children;
};

#endif // PARSE_GENERIC_LIST_H
